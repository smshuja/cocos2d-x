#ifndef __eureekah_h__
#define __eureekah_h__

#include "jsapi.h"
#include "jsfriendapi.h"


extern JSClass  *jsb_Utilities_class;
extern JSObject *jsb_Utilities_prototype;

JSBool js_eureekah_Utilities_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_eureekah_Utilities_finalize(JSContext *cx, JSObject *obj);
void js_register_eureekah_Utilities(JSContext *cx, JSObject *global);
void register_all_eureekah(JSContext* cx, JSObject* obj);
JSBool js_eureekah_Utilities_openUrl(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_eureekah_Utilities_getResourceDirectory(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_eureekah_Utilities_Utilities(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_ProductManager_class;
extern JSObject *jsb_ProductManager_prototype;

JSBool js_eureekah_ProductManager_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_eureekah_ProductManager_finalize(JSContext *cx, JSObject *obj);
void js_register_eureekah_ProductManager(JSContext *cx, JSObject *global);
void register_all_eureekah(JSContext* cx, JSObject* obj);
JSBool js_eureekah_ProductManager_restore(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_eureekah_ProductManager_isProductPurchased(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_eureekah_ProductManager_buyProduct(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_eureekah_ProductManager_getClassTypeInfo(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_eureekah_ProductManager_isBusy(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_eureekah_ProductManager_getProductPrice(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_eureekah_ProductManager_sharedInstance(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_eureekah_ProductManager_ProductManager(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_GoogleAnalytics_class;
extern JSObject *jsb_GoogleAnalytics_prototype;

JSBool js_eureekah_GoogleAnalytics_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_eureekah_GoogleAnalytics_finalize(JSContext *cx, JSObject *obj);
void js_register_eureekah_GoogleAnalytics(JSContext *cx, JSObject *global);
void register_all_eureekah(JSContext* cx, JSObject* obj);
JSBool js_eureekah_GoogleAnalytics_trackScreen(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_eureekah_GoogleAnalytics_trackEvent(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_eureekah_GoogleAnalytics_setCustomDimensionForIndex(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_eureekah_GoogleAnalytics_GoogleAnalytics(JSContext *cx, uint32_t argc, jsval *vp);
#endif

