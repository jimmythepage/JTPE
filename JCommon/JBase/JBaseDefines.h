#ifndef JBASEDEFINES
#define JBASEDEFINES

#define JNEWLINE			_JNEWLINE

#ifdef __ANDROID__
#define _JNEWLINE '\rn'
#elif __APPLE__
#define _JNEWLINE '\r'
#elif __WINDOWS__
#define _JNEWLINE '\n'
#endif

#define JBUILD_FILES		"BUILD_FILES"
#define JDATA_FILES			"JDATA_FILES"

#define LOG_INFO _LOG_INFO
#define LOG_WARNING _LOG_WARNING

#define ASSERT __ASSERT
#define EXIT   __EXIT


#ifdef _JDEBUG_
	#ifdef __ANDROID__
		#define _LOG_INFO(...)		((void)__android_log_print(ANDROID_LOG_INFO, "AndroidProject1.NativeActivity", __VA_ARGS__))
		#define _LOG_WARNING(...)	((void)__android_log_print(ANDROID_LOG_WARN, "AndroidProject1.NativeActivity", __VA_ARGS__))
	#elif __APPLE__
		#define _LOG_INFO(...)		((void)0)
		#define _LOG_WARNING(...)	((void)0)
	#elif __WINDOWS__
		#define _LOG_INFO			_RPT1
		#define _LOG_WARNING(...)	((void)0)
	#endif
	#define __ASSERT(...)			assert(__VA_ARGS__)
	#define __EXIT(...)				exit(__VA_ARGS__)
#else
	#define _LOG_INFO(...)			((void)0)
	#define _LOG_WARNING(...)		((void)0)
	#define __ASSERT(...)			((void)0)
	#define __EXIT(...)			((void)0)
#endif

enum PlayStyle
{
	NONE,
	FORWARD,
	BACKWARD,
	PINGPONG
};

enum PlayCurve
{
	LINEAR,
	PUNCH_IN,
	PUNCH_OUT
};

#endif // !JBASEDEFINES
