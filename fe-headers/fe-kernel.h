#ifndef FE_KERNEL_H
#define FE_KERNEL_H

#ifdef __cplusplus
extern "C" {
#endif

extern volatile int fe_status;
void fe_main();
void fe_panic();

#ifdef __cplusplus
}
#endif

#endif // FE_KERNEL_H
