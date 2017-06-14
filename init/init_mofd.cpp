/*
** Copyright 2016, The CyanogenMod Project
**
** Licensed under the Apache License, Version 2.0 (the "License");
** you may not use this file except in compliance with the License.
** You may obtain a copy of the License at
**
**     http://www.apache.org/licenses/LICENSE-2.0
**
** Unless required by applicable law or agreed to in writing, software
** distributed under the License is distributed on an "AS IS" BASIS,
** WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
** See the License for the specific language governing permissions and
** limitations under the License.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#define _REALLY_INCLUDE_SYS__SYSTEM_PROPERTIES_H_
#include <sys/_system_properties.h>

#include "log.h"
#include "property_service.h"
#include "util.h"
#include "vendor_init.h"

#define STRCONV_(x)      #x
#define STRCONV(x) "%" STRCONV_(x) "s"

#define PHONE_INFO "/factory/PhoneInfodisk/PhoneInfo_inf"
#define BUF_SIZE 64

/* Serial number */
#define SERIAL_PROP "ro.serialno"
#define SERIAL_OFFSET 0x00
#define SERIAL_LENGTH 17

/* Cpufreq */
#define MAX_CPU_FREQ    "/sys/devices/system/cpu/cpu0/cpufreq/cpuinfo_max_freq"
#define LOW_CPU "1833000"
#define HIGH_CPU "2333000"

/* Zram */
#define ZRAM_PROP "ro.config.zram"
#define MEMINFO_FILE "/proc/meminfo"
#define MEMINFO_KEY "MemTotal:"
#define ZRAM_MEM_THRESHOLD 3000000

/* Intel kernel paths */
char const *intel_path[] = {
"/sys/kernel/fw_update/fw_info/ifwi_version",
"/sys/kernel/fw_update/fw_info/chaabi_version",
"/sys/kernel/fw_update/fw_info/mia_version",
"/sys/kernel/fw_update/fw_info/scu_bs_version",
"/sys/kernel/fw_update/fw_info/scu_version",
"/sys/kernel/fw_update/fw_info/ia32fw_version",
"/sys/kernel/fw_update/fw_info/valhooks_version",
"/sys/kernel/fw_update/fw_info/punit_version",
"/sys/kernel/fw_update/fw_info/ucode_version",
"/sys/kernel/fw_update/fw_info/pmic_nvm_version",
"/sys/devices/virtual/misc/watchdog/counter",
"/proc/sys/kernel/osrelease"
};

/* Intel props */
char const *intel_prop[] = {
"sys.ifwi.version",
"sys.chaabi.version",
"sys.mia.version",
"sys.scu_bs.version",
"sys.scu.version",
"sys.ia32fw.version",
"sys.valhooks.version",
"sys.punit.version",
"sys.ucode.version",
"sys.pmic_nvm.version",
"sys.watchdog.previous.counter",
"sys.kernel.version"
};

static int read_file2(const char *fname, char *data, int max_size)
{
    int fd, rc;

    if (max_size < 1)
        return 0;

    fd = open(fname, O_RDONLY);
    if (fd < 0) {
        ERROR("failed to open '%s'\n", fname);
        return 0;
    }

    rc = read(fd, data, max_size -1);
    if ((rc > 0) && (rc < max_size ))
        data[rc] = '\0';
    else
        data[0] = '\0';
    close(fd);

    return 1;
}

static void get_serial()
{
    int ret = 0;
    char const *path = PHONE_INFO;
    char buf[SERIAL_LENGTH + 1];
    char value[BUF_SIZE];
    prop_info *pi;

    if(read_file2(path, buf, sizeof(buf))) {
        if (strlen(buf) > 0) {
            pi = (prop_info*) __system_property_find(SERIAL_PROP);
            if(pi)
                ret = __system_property_update(pi, buf,
                        strlen(buf));
            else
                ret = __system_property_add(SERIAL_PROP,
                        strlen(SERIAL_PROP),
                        buf, strlen(buf));
        }
    }
}

static void configure_zram() {
    char buf[128];
    FILE *f;

    if ((f = fopen(MEMINFO_FILE, "r")) == NULL) {
        ERROR("%s: Failed to open %s\n", __func__, MEMINFO_FILE);
        return;
    }

    while (fgets(buf, sizeof(buf), f) != NULL) {
        if (strncmp(buf, MEMINFO_KEY, strlen(MEMINFO_KEY)) == 0) {
            int mem = atoi(&buf[strlen(MEMINFO_KEY)]);
            const char *mode = mem < ZRAM_MEM_THRESHOLD ? "true" : "false";
            INFO("%s: Found total memory to be %d kb, zram enabled: %s\n", __func__, mem, mode);
            property_set(ZRAM_PROP, mode);
            break;
        }
    }

    fclose(f);
}

static void intel_props() {

    char buf[BUF_SIZE];
    char value[BUF_SIZE];
    for(int i=0; i<12; i++) {
        if(read_file2(intel_path[i], buf, sizeof(buf))) {
            sscanf(buf, STRCONV(BUF_SIZE), value);
            property_set(intel_prop[i],value);
        }
    }

}

void set_feq_values()
{
    char buf[BUF_SIZE];

    if(read_file2(MAX_CPU_FREQ, buf, sizeof(buf))) {
	if ( strncmp(buf, LOW_CPU, strlen(LOW_CPU)) == 0 ) {
            property_set("ro.sys.perf.device.powersave", "1250000");
            property_set("ro.sys.perf.device.touchboost", "500000");
            property_set("ro.sys.perf.device.full", "1833000");
        } else if ( strncmp(buf, HIGH_CPU, strlen(HIGH_CPU)) == 0 ) {
            property_set("ro.sys.perf.device.powersave", "1500000");
            property_set("ro.sys.perf.device.touchboost", "1833000");
            property_set("ro.sys.perf.device.full", "2333000");
        } else {
            INFO("%s: Failed to get max cpu speed: %s\n", __func__, buf);
        }
    }
}

void vendor_load_properties()
{
    get_serial();
    configure_zram();
    intel_props();
    set_feq_values();
}
