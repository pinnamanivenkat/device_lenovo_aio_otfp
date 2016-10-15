#define LOG_TAG "bule"

#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>

#include <cutils/properties.h>
#include <cutils/log.h>
#include <private/android_filesystem_config.h>


static void s_mknod(const char *pathname, mode_t type, unsigned int maj, unsigned int min)
{
    mknod(pathname, type, makedev(maj, min));
}


static void s_mkdirp(const char *pathname)
{
    char buf[PATH_MAX];
    char currpath[PATH_MAX], *pathpiece;
    struct stat st;
    int ret;

    // buffer for strtok
    // hopefully the strings are not too long
    strncpy(buf, pathname, PATH_MAX);

    // reset path
    strcpy(currpath, "");
    // create the pieces of the path along the way
    pathpiece = strtok(buf, "/");
    if(buf[0] == '/') {
        // prepend / if needed
        strcat(currpath, "/");
    }
    while(pathpiece != NULL) {
        if(strlen(currpath) + strlen(pathpiece) + 2/*NUL and slash*/ > PATH_MAX) {
            ALOGE("Invalid path specified: too long");
            return;  // return 1;
        }
        strcat(currpath, pathpiece);
        strcat(currpath, "/");
        if(stat(currpath, &st) != 0) {
            ret = mkdir(currpath, 0777);
            if(ret < 0) {
                ALOGE("mkdir failed for %s, %s\n", currpath, strerror(errno));
                return;  // return ret;
            }
        }
        pathpiece = strtok(NULL, "/");
    }
}


#if 0
static void s_echo(const char *pathname, const void *buf, size_t len)
{
    int fd;
    int remaining;
    int ret;
    fd = open(pathname, O_WRONLY);
    if (fd < 0) {
        ALOGE("echo: failed to open file %s: %s", pathname, strerror(errno));
        return;
    }
    remaining = len;
    while (remaining) {
        ret = write(fd, buf, remaining);
        if (ret < 0) {
            ALOGE("echo: write failed: %s", strerror(errno));
            goto bail;
        }
        remaining -= ret;
    }
bail:
    close(fd);
}
#endif


int main(int argc __attribute__((unused)), char **argv __attribute__((unused)))
{
    ALOGI("starting");

    // on post-fs-data
    //
    // Connectivity related device nodes & configuration (begin)
    //

// /dev/ttyMT2 for Connectivity BT/FM/GPS usage
    chmod("/dev/ttyMT2", 0660);
    chown("/dev/ttyMT2", AID_SYSTEM, AID_SYSTEM);

//Camera
    chmod("/dev/GAF001AF", 0660);
    chown("/dev/GAF001AF", AID_SYSTEM, AID_CAMERA);

    chmod("/dev/DW9714AF", 0660);
    chown("/dev/DW9714AF", AID_SYSTEM, AID_CAMERA);

    chmod("/dev/AD5820AF", 0660);
    chown("/dev/AD5820AF", AID_SYSTEM, AID_CAMERA);

    chmod("/dev/BU64745GWZAF", 0660);
    chown("/dev/BU64745GWZAF", AID_SYSTEM, AID_CAMERA);

//SMB
    chown("/proc/smb/ScreenComm", AID_SYSTEM, AID_SYSTEM);
    chmod("/proc/smb/ScreenComm", 0660);

    // Create char device file for WMT, GPS, BT, FM, WIFI
    // xen0n: stp stands for setup... oh what English is this
    // don't know why they're commented out in Flyme, at least the bluetooth one
    // seems to be required in proper bluetooth initialization...
     //s_mknod("/dev/stpwmt", S_IFCHR, 190, 0);
     //s_mknod("/dev/stpgps", S_IFCHR, 191, 0);
     //s_mknod("/dev/stpbt", S_IFCHR, 192, 0);

     //chmod("/dev/stpwmt", 0660);
     //chown("/dev/stpwmt", AID_SYSTEM, AID_SYSTEM);

     //chmod("/dev/wmtdetect", 0660);
     //chown("/dev/wmtdetect", AID_SYSTEM, AID_SYSTEM);

    s_mknod("/dev/wmtWifi", S_IFCHR, 153, 0);
    chmod("/dev/wmtWifi", 0660);
    chown("/dev/wmtWifi", AID_SYSTEM, AID_SYSTEM);

    // BT
    chmod("/dev/stpbt", 0660);
    chown("/dev/stpbt", AID_BLUETOOTH, AID_RADIO);
   
   // BT 3.0 HS
    s_mknod("/dev/ampc0", S_IFCHR, 151, 0);
    chmod("/dev/ampc0", 0660);
    chown("/dev/ampc0", AID_BLUETOOTH, AID_BLUETOOTH);

    // GPS
    chown("/dev/stpgps", AID_GPS, AID_GPS);
    chown("/sys/class/gpsdrv/gps/pwrctl", AID_GPS, AID_GPS);
    chown("/sys/class/gpsdrv/gps/suspend", AID_GPS, AID_GPS);
    chown("/sys/class/gpsdrv/gps/state", AID_GPS, AID_GPS);
    chown("/sys/class/gpsdrv/gps/pwrsave", AID_GPS, AID_GPS);
    chown("/sys/class/gpsdrv/gps/status", AID_GPS, AID_GPS);
    chmod("/dev/stpgps", 0660);

    // WiFi
    s_mkdirp("/data/misc/wifi");
    chmod("/data/misc/wifi", 0770);
    chown("/data/misc/wifi", AID_WIFI, AID_WIFI);
    s_mkdirp("/data/misc/wifi/sockets");
    chmod("/data/misc/wifi/sockets", 0770);
    chown("/data/misc/wifi/sockets", AID_WIFI, AID_WIFI);
    s_mkdirp("/data/misc/wpa_supplicant");
    chmod("/data/misc/wpa_supplicant", 0770);
    chown("/data/misc/wpa_supplicant", AID_WIFI, AID_WIFI);
    chown("/data/misc/wifi", AID_WIFI, AID_WIFI);

    // ATCID
    chmod("/dev/ttyGS0", 0660);
    chown("/dev/ttyGS0", AID_SYSTEM, AID_SYSTEM);
    chmod("/dev/ttyGS1", 0660);
    chown("/dev/ttyGS1", AID_SYSTEM, AID_SYSTEM);

    // piezo
    chown("/sys/class/switch/piezo/state", AID_SYSTEM, AID_SYSTEM);

    // limm3
    chmod("/sys/class/power_supply/battery/charging_led_flag", 0664);
    chown("system system /sys/class/power_supply/battery/charging_led_flag", AID_SYSTEM, AID_SYSTEM);

    // ANT
    chmod("/dev/stpant", 0660);
    chown("/dev/stpant", AID_SYSTEM, AID_SYSTEM);

    // Vcodec
    s_mknod("/dev/Vcodec", S_IFCHR, 160, 0);
    chmod("/dev/Vcodec", 0660);
    chown("/dev/Vcodec", AID_SYSTEM, AID_MEDIA);

    // FM Radio device node
    s_mknod("/dev/fm", S_IFCHR, 193, 0);
    chmod("/dev/fm", 0660);
    chown("/dev/fm", AID_SYSTEM, AID_MEDIA);

    // device info /proc interface
    s_mknod("/dev/devmap", S_IFCHR, 196, 0);
    chmod("/dev/devmap", 0440);
    chown("/dev/devmap", AID_ROOT, AID_SYSTEM);

	// Encrypt phone function
	property_set("vold.post_fs_data_done", "1");

    ALOGI("exiting");

    return 0;
}
