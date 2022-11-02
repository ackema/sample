#ifndef _UTILS_H_
#define _UTILS_H_

#define safe_free(m)  \
    do                \
    {                 \
        if (m)        \
        {             \
            free(m);  \
            m = NULL; \
        }             \
    } while (0)

#define safe_close(fd) \
    do                 \
    {                  \
        if (fd)        \
        {              \
            close(fd); \
            fd = -1;   \
        }              \
    } while (0)

#define safe_fclose(fp) \
    do                 \
    {                  \
        if (fp)        \
        {              \
            fclose(fp); \
            fp = NULL;   \
        }              \
    } while (0)


#endif
