#include <fcntl.h>
#include <unistd.h>
#include "constant.h"
#include "utils.h"

static char *g_psv_string[_PSV_BORDER] = {_PSV_EXIT_STRING, _PSV_ACTIVE_STRING, _PSV_EXCEPT_STRING, _PSV_SLEEP_STRING};

int _clog_init(void)
{
    return dzlog_init(_LOG_CONF_FILE, _LOG_RULES_DEFAULT);    
}

bool is_active(psv_t psv)
{
    return (psv == _PSV_ACTIVE);
}

bool is_except(psv_t psv)
{
    return (psv == _PSV_EXCEPT);
}


bool is_sleep(psv_t psv)
{
    return (psv == _PSV_SLEEP);
}

bool is_exit(psv_t psv)
{
    return (psv == _PSV_EXIT);
}

bool is_online(void)
{
    int fd = open(_PROCESS_STATUS_FILE, O_RDONLY);
    if (fd < 0)
    {
        return false;
    }

    close(fd);
    return true;
}

psv_t set_psv(psv_t psv)
{
    int fd = open(_PROCESS_STATUS_FILE, O_WRONLY | O_CREAT, 0666);
    if (fd < 0)
    {
        clog_error("Failed to create|open process status file.");
        return -1;
    }

    if (write(fd, &psv, sizeof(psv)) < 1)
    {
        clog_error("Failed to set process status value.");
        close(fd);
        return -1;
    }

    close(fd);
    return 0;
}

psv_t get_psv(void)
{
    int fd = open(_PROCESS_STATUS_FILE, O_RDONLY);
    if (fd < 0)
    {
        clog_error("Failed to open process status file.");
        return -1;
    }
    psv_t psv = 0;
    if (read(fd, &psv, sizeof(psv)) < 1)
    {
        clog_error("Failed to get process status value.");
        close(fd);
        return -1;
    }

    close(fd);
    return psv;
}

char *to_psvstring(psv_t psv)
{
    if (psv < 0 || psv >= _PSV_BORDER)
    {
        clog_error("Invalid process status value");
        return NULL;
    }

    return g_psv_string[psv];
}