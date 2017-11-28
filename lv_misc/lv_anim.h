/**
 * @file anim.h
 *
 */

#ifndef ANIM_H
#define ANIM_H

#ifdef __cplusplus
extern "C" {
#endif


/*********************
 *      INCLUDES
 *********************/
#include "../../lv_conf.h"
#if LV_NO_ANIM == 0

#include <stdint.h>
#include <stdbool.h>

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

typedef enum
{
	LV_ANIM_PATH_LIN,
	LV_ANIM_PATH_STEP,
}lv_anim_path_name_t;

typedef uint8_t lv_anim_path_t;

typedef void (*lv_anim_fp_t)(void *, int32_t);
typedef void (*lv_anim_cb_t)(void *);

typedef struct
{
	void * var;						/*Variable to animate*/
	lv_anim_fp_t fp;	/*Animator function*/
	lv_anim_cb_t end_cb;		/*Call it when the animation is ready*/
	lv_anim_path_t * path;			/*An array with the steps of animations*/
	int32_t start;					/*Start value*/
	int32_t end;					/*End value*/
	int16_t time;					/*Animation time in ms*/
	int16_t act_time;				/*Current time in animation. Set to negative to make delay.*/
	uint16_t playback_pause;		/*Wait before play back*/
	uint16_t repeat_pause;			/*Wait before repeat*/
	uint8_t playback :1;			/*When the animation is ready play it back*/
	uint8_t repeat :1;				/*Repeat the animation infinitely*/
	/*Animation system use these - user shouldn't set*/
	uint8_t playback_now :1;		/*Play back is in progress*/
}lv_anim_t;

/*Example initialization
lv_anim_t a;
a.var = obj;
a.start = lv_obj_get_height(obj);
a.end = new_height;
a.fp = (anim_fp_t)lv_obj_set_height;
a.path = anim_get_path(ANIM_PATH_LIN);
a.end_cb = NULL;
a.act_time = 0;
a.time = 200;
a.playback = 0;
a.playback_pause = 0;
a.repeat = 0;
a.repeat_pause = 0;
 */
/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * Init. the animation module
 */
void lv_anim_init(void);

/**
 * Create an animation
 * @param anim_p an initialized 'anim_t' variable. Not required after call.
 */
void lv_anim_create(lv_anim_t * anim_p);

/**
 * Delete an animation for a variable with a given animatior function
 * @param var pointer to variable
 * @param fp a function pointer which is animating 'var',
 *           or NULL to ignore it and delete all animation with 'var
 * @return true: at least 1 animation is deleted, false: no animation is deleted
 */
bool lv_anim_del(void * var, lv_anim_fp_t fp);

/**
 * Calculate the time of an animation with a given speed and the start and end values
 * @param speed speed of animation in unit/sec
 * @param start start value of the animation
 * @param end end value of the animation
 * @return the required time [ms] for the animation with the given parameters
 */
uint16_t lv_anim_speed_to_time(uint16_t speed, int32_t start, int32_t end);

/**
 * Get a predefine animation path
 * @param name name of the path from 'anim_path_name_t'
 * @return pointer to the path array
 */
lv_anim_path_t * lv_anim_get_path(lv_anim_path_name_t name);

/**********************
 *      MACROS
 **********************/

#endif /*LV_NO_ANIM == 0*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*LV_ANIM_H*/

