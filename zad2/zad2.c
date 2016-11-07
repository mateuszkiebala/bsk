#include "unit_tests.h"
#include "run.h"
#include <stdio.h>
#include <security/pam_appl.h>
#include <security/pam_misc.h>

#define SERVICE_NAME "zad2"
#define USER_PROMPT "Badania korpusowe?"

static struct pam_conv conv = {
    misc_conv,
    NULL
};

int main(int argc, char const *argv[])
{
    pam_handle_t* pamh = NULL;
    char *username = NULL;
    
    int r = pam_start(SERVICE_NAME, username, &conv, &pamh);
    if (pamh == NULL || r != PAM_SUCCESS) {
        fprintf(stderr, "Error when starting: %d (%s)\n", r, pam_strerror(pamh, r));
        exit(1);
    }
    
    r = pam_set_item(pamh, PAM_USER_PROMPT, USER_PROMPT);
    if (r != PAM_SUCCESS) {
        fprintf(stderr, "Unable to set PAM config: %d (%s)", r, pam_strerror(pamh, r));
        exit(2);
    }

    r = pam_authenticate(pamh, 0);
    if (r != PAM_SUCCESS) {
        fprintf(stderr, "Unable to authenticate: %d (%s)\n", r, pam_strerror(pamh, r));
        exit(3);
    }

    r = pam_acct_mgmt(pamh, PAM_SILENT | PAM_DISALLOW_NULL_AUTHTOK);
    if(r != PAM_SUCCESS) {
        fprintf(stderr, "Access denied: %d (%s)", r, pam_strerror(pamh, r));
        exit(4);
    }

    pam_end(pamh, PAM_SUCCESS);

    test();
    return run(stdin, stdout);
}
