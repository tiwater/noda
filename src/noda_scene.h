#ifndef __NODA_SCENE_H
#define __NODA_SCENE_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    int (*on_load) (void);
    int (*on_exit) (void);
    int (*on_show) (void);
    int (*on_hide) (void);

    int (*to_scene) (void);
} noda_scene_t;

#ifdef __cplusplus
}
#endif

#endif // __NODA_SCENE_H
