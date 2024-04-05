#include <IOKit/graphics/IOGraphicsLib.h>
#include <ApplicationServices/ApplicationServices.h>
#include <unistd.h>
#include <math.h>
#include <stdio.h>

void printScreenInfo(int idx, int displayId) {
    UInt32 isPrimary = CGDisplayIsMain(displayId);
    UInt32 isBuiltIn = CGDisplayIsBuiltin(displayId);
    float x = CGDisplayBounds(displayId).origin.x;
    float y = CGDisplayBounds(displayId).origin.y;
    printf("external%d: displayId:%d primary: %d, builtIn: %d x:%f y:%f\n", idx, displayId, isPrimary, isBuiltIn, x, y);
}

void swapDisplays(UInt32 display1, UInt32 display2) {
    CGDisplayConfigRef configRef;
    CGBeginDisplayConfiguration(&configRef);

    UInt32 leftDisplay = display1;
    UInt32 rightDisplay = display2;
    if (leftDisplay > rightDisplay) {
        leftDisplay = display2;
        rightDisplay = display1;
    }

    float leftX = CGDisplayBounds(leftDisplay).origin.x;
    float leftY = CGDisplayBounds(leftDisplay).origin.y;
    float rightX = CGDisplayBounds(rightDisplay).origin.x;
    float rightY = CGDisplayBounds(rightDisplay).origin.y;


    if (leftX == 0) { 
        // left is current primary display. Make right as primary
	if (rightX < 0) {
            rightX = -1 * rightX;
        }
        CGConfigureDisplayOrigin(configRef, leftDisplay, rightX, rightY);
    } else {
        // right is current primary display. Make left as primary
        if (leftX > 0) {
            leftX = -1 * leftX;
        }
    }
    CGConfigureDisplayOrigin(configRef, leftDisplay, rightX, rightY);
    CGConfigureDisplayOrigin(configRef, rightDisplay, leftX, leftY);

    CGCompleteDisplayConfiguration(configRef, kCGConfigurePermanently);
}

int main(int argc, const char * argv[]) {

    CGDirectDisplayID screenList[3];
    CGDirectDisplayID externalScreenList[2];
    UInt32 displayCount;
    CGGetActiveDisplayList(INT_MAX, screenList, &displayCount);

    int externalDisplayCount = 0; 
    for (int i=0; i < displayCount; i++) {
	CGDirectDisplayID displayId = screenList[i];
        if (!CGDisplayIsBuiltin(displayId)) {
            externalScreenList[externalDisplayCount++] = displayId;
        }
    }
    printf("Display Total: %d, External: %d\n", displayCount, externalDisplayCount);
    for (int i=0; i < externalDisplayCount; i++) {
        printScreenInfo(i, externalScreenList[i]);
    }

    if (externalDisplayCount == 2) {
        swapDisplays(externalScreenList[0], externalScreenList[1]);
    }

    printf("Updated displays:\n");
    for (int i=0; i < externalDisplayCount; i++) {
        printScreenInfo(i, externalScreenList[i]);
    }
}
