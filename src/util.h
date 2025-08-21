#include <string.h>
#include <stdarg.h>

#ifdef ORBIS
#include <orbis/libkernel.h>
#endif

inline static void send_notification(const char* FMT, ...)
{
	#ifdef ORBIS
	OrbisNotificationRequest Buffer;

	va_list args;
	va_start(args, FMT);
	vsprintf(Buffer.message, FMT, args);
	va_end(args);

	Buffer.type = OrbisNotificationRequestType::NotificationRequest;
	Buffer.unk3 = 0;
	Buffer.useIconImageUri = 1;
	Buffer.targetId = -1;
	strcpy(Buffer.iconUri, "cxml://psnotification/tex_icon_system");

	sceKernelSendNotificationRequest(0, &Buffer, 3120, 0);
	#else
	va_list args;
	va_start(args, FMT);
	vprintf(FMT, args);
	va_end(args);
	printf("\n");
	#endif
}

inline static void KernelPrintOut(const char* FMT, ...)
{
	#ifdef ORBIS
	char MessageBuf[1024];
	va_list args;
	va_start(args, FMT);
	vsprintf(MessageBuf, FMT, args);
	va_end(args);

	sceKernelDebugOutText(0, MessageBuf);
	#else
	va_list args;
	va_start(args, FMT);
	vprintf(FMT, args);
	va_end(args);
	printf("\n");
	#endif
}