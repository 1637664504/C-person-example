extern FILE *xlog_fp;
#define LIUJ_LOG_FILE "/tmp/liuj.log"
extern int xlog_init(void);
extern void xlog_close(void);
#define xlogf(format, args...) fprintf(xlog_fp,format,args)
#define xlog_debug(format, args...) fprintf(xlog_fp,"%s:%d "format,__func__,__LINE__,args)