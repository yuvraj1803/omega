#include "auth/auth.h"
#include "stdio.h"
#include "config.h"
#include "fs/ff.h"
#include "string.h"

char monitor_key[OMEGA_KEY_SIZE];
#define PASSWD_FILENAME     "/passwd.txt"

void auth_init(){

    FILINFO fno;
    FIL passwd_file;


    /* If the password is never set-up, there will be no /passwd file.*/

    if(f_stat(PASSWD_FILENAME, &fno) == FR_NO_FILE){
        printf("Enter Passphrase for Secure Monitor: ");
        gets(monitor_key);

        uint16_t key_size = strlen(monitor_key);
        
        if(f_open(&passwd_file, PASSWD_FILENAME, FA_OPEN_ALWAYS | FA_WRITE | FA_READ) < FR_OK){
            panic("Passphrase file could not be initialised.");
        }

        unsigned int bytes_written;
        f_write(&passwd_file, monitor_key, key_size, &bytes_written);

        if(bytes_written != key_size){
            panic("Passphrase could not be saved.");
        }

        goto out;
    }   

    if(f_open(&passwd_file, PASSWD_FILENAME, FA_OPEN_EXISTING | FA_READ) != FR_OK){
        panic("Passphrase file could not be opened.");
    }

    unsigned int bytes_read;

    if(f_read(&passwd_file, monitor_key, OMEGA_KEY_SIZE, &bytes_read) != FR_OK){
        panic("Passphrase file could not be read.");
    }

    printf("Enter Passphrase for Secure Monitor: ");
    char key_entered[OMEGA_KEY_SIZE];
    gets(key_entered);

    if(strcmp(key_entered, monitor_key)){
        panic("Wrong key entered.");
    }

    out:

    f_close(&passwd_file);
    log("Authentication Successful.");
}