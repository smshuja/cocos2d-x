#include "eureekah.hpp"
#include "cocos2d_specifics.hpp"
#include "Utilities.h"
#include "ProductManager.h"
#include "GoogleAnalytics.h"

template<class T>
static JSBool dummy_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
	TypeTest<T> t;
	T* cobj = new T();
	js_type_class_t *p;
	uint32_t typeId = t.s_id();
	HASH_FIND_INT(_js_global_type_ht, &typeId, p);
	assert(p);
	JSObject *_tmp = JS_NewObject(cx, p->jsclass, p->proto, p->parentProto);
	js_proxy_t *pp = jsb_new_proxy(cobj, _tmp);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(_tmp));

	return JS_TRUE;
}

static JSBool empty_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
	return JS_FALSE;
}


JSClass  *jsb_Utilities_class;
JSObject *jsb_Utilities_prototype;

JSBool js_eureekah_Utilities_openUrl(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	if (argc == 1) {
		const char* arg0;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		Eureekah::Utilities::openUrl(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}
	JS_ReportError(cx, "wrong number of arguments");
	return JS_FALSE;
}

JSBool js_eureekah_Utilities_getResourceDirectory(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		std::string ret = Eureekah::Utilities::getResourceDirectory();
		jsval jsret;
		jsret = std_string_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}
	JS_ReportError(cx, "wrong number of arguments");
	return JS_FALSE;
}

JSBool js_eureekah_Utilities_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		Eureekah::Utilities* cobj = new Eureekah::Utilities();
		TypeTest<Eureekah::Utilities> t;
		js_type_class_t *typeClass;
		uint32_t typeId = t.s_id();
		HASH_FIND_INT(_js_global_type_ht, &typeId, typeClass);
		assert(typeClass);
		JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
		JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
		// link the native object with the javascript object
		js_proxy_t* p = jsb_new_proxy(cobj, obj);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}




void js_eureekah_Utilities_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (Utilities)", obj);
    js_proxy_t* nproxy;
    js_proxy_t* jsproxy;
    jsproxy = jsb_get_js_proxy(obj);
    if (jsproxy) {
        nproxy = jsb_get_native_proxy(jsproxy->ptr);

        Eureekah::Utilities *nobj = static_cast<Eureekah::Utilities *>(nproxy->ptr);
        if (nobj)
            delete nobj;
        
        jsb_remove_proxy(nproxy, jsproxy);
    }
}

static JSBool js_eureekah_Utilities_ctor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
    Eureekah::Utilities *nobj = new Eureekah::Utilities();
    js_proxy_t* p = jsb_new_proxy(nobj, obj);
    JS_SET_RVAL(cx, vp, JSVAL_VOID);
    return JS_TRUE;
}

void js_register_eureekah_Utilities(JSContext *cx, JSObject *global) {
	jsb_Utilities_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_Utilities_class->name = "Utilities";
	jsb_Utilities_class->addProperty = JS_PropertyStub;
	jsb_Utilities_class->delProperty = JS_PropertyStub;
	jsb_Utilities_class->getProperty = JS_PropertyStub;
	jsb_Utilities_class->setProperty = JS_StrictPropertyStub;
	jsb_Utilities_class->enumerate = JS_EnumerateStub;
	jsb_Utilities_class->resolve = JS_ResolveStub;
	jsb_Utilities_class->convert = JS_ConvertStub;
	jsb_Utilities_class->finalize = js_eureekah_Utilities_finalize;
	jsb_Utilities_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	JSPropertySpec *properties = NULL;

	JSFunctionSpec *funcs = NULL;

	static JSFunctionSpec st_funcs[] = {
		JS_FN("openUrl", js_eureekah_Utilities_openUrl, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getResourceDirectory", js_eureekah_Utilities_getResourceDirectory, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};

	jsb_Utilities_prototype = JS_InitClass(
		cx, global,
		NULL, // parent proto
		jsb_Utilities_class,
		js_eureekah_Utilities_constructor, 0, // constructor
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
	JSBool found;
	JS_SetPropertyAttributes(cx, global, "Utilities", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<Eureekah::Utilities> t;
	js_type_class_t *p;
	uint32_t typeId = t.s_id();
	HASH_FIND_INT(_js_global_type_ht, &typeId, p);
	if (!p) {
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->type = typeId;
		p->jsclass = jsb_Utilities_class;
		p->proto = jsb_Utilities_prototype;
		p->parentProto = NULL;
		HASH_ADD_INT(_js_global_type_ht, type, p);
	}
}


JSClass  *jsb_ProductManager_class;
JSObject *jsb_ProductManager_prototype;

JSBool js_eureekah_ProductManager_restore(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	Eureekah::ProductManager* cobj = (Eureekah::ProductManager *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 0) {
		cobj->restore();
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_eureekah_ProductManager_isProductPurchased(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	Eureekah::ProductManager* cobj = (Eureekah::ProductManager *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 1) {
		const char* arg0;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		bool ret = cobj->isProductPurchased(arg0);
		jsval jsret;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_eureekah_ProductManager_buyProduct(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	Eureekah::ProductManager* cobj = (Eureekah::ProductManager *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 1) {
		const char* arg0;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->buyProduct(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_eureekah_ProductManager_getClassTypeInfo(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	Eureekah::ProductManager* cobj = (Eureekah::ProductManager *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 0) {
		long ret = cobj->getClassTypeInfo();
		jsval jsret;
		#pragma warning NO CONVERSION FROM NATIVE FOR long;
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_eureekah_ProductManager_isBusy(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	Eureekah::ProductManager* cobj = (Eureekah::ProductManager *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 0) {
		bool ret = cobj->isBusy();
		jsval jsret;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_eureekah_ProductManager_getProductPrice(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	Eureekah::ProductManager* cobj = (Eureekah::ProductManager *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 1) {
		const char* arg0;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		const char* ret = cobj->getProductPrice(arg0);
		jsval jsret;
		jsret = c_string_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_eureekah_ProductManager_sharedInstance(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		Eureekah::ProductManager* ret = Eureekah::ProductManager::sharedInstance();
		jsval jsret;
		do {
		if (ret) {
			js_proxy_t *proxy = js_get_or_create_proxy<Eureekah::ProductManager>(cx, ret);
			jsret = OBJECT_TO_JSVAL(proxy->obj);
		} else {
			jsret = JSVAL_NULL;
		}
	} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}
	JS_ReportError(cx, "wrong number of arguments");
	return JS_FALSE;
}

JSBool js_eureekah_ProductManager_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		Eureekah::ProductManager* cobj = new Eureekah::ProductManager();
		TypeTest<Eureekah::ProductManager> t;
		js_type_class_t *typeClass;
		uint32_t typeId = t.s_id();
		HASH_FIND_INT(_js_global_type_ht, &typeId, typeClass);
		assert(typeClass);
		JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
		JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
		// link the native object with the javascript object
		js_proxy_t* p = jsb_new_proxy(cobj, obj);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}




void js_eureekah_ProductManager_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (ProductManager)", obj);
    js_proxy_t* nproxy;
    js_proxy_t* jsproxy;
    jsproxy = jsb_get_js_proxy(obj);
    if (jsproxy) {
        nproxy = jsb_get_native_proxy(jsproxy->ptr);

        Eureekah::ProductManager *nobj = static_cast<Eureekah::ProductManager *>(nproxy->ptr);
        if (nobj)
            delete nobj;
        
        jsb_remove_proxy(nproxy, jsproxy);
    }
}

static JSBool js_eureekah_ProductManager_ctor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
    Eureekah::ProductManager *nobj = new Eureekah::ProductManager();
    js_proxy_t* p = jsb_new_proxy(nobj, obj);
    JS_SET_RVAL(cx, vp, JSVAL_VOID);
    return JS_TRUE;
}

void js_register_eureekah_ProductManager(JSContext *cx, JSObject *global) {
	jsb_ProductManager_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_ProductManager_class->name = "ProductManager";
	jsb_ProductManager_class->addProperty = JS_PropertyStub;
	jsb_ProductManager_class->delProperty = JS_PropertyStub;
	jsb_ProductManager_class->getProperty = JS_PropertyStub;
	jsb_ProductManager_class->setProperty = JS_StrictPropertyStub;
	jsb_ProductManager_class->enumerate = JS_EnumerateStub;
	jsb_ProductManager_class->resolve = JS_ResolveStub;
	jsb_ProductManager_class->convert = JS_ConvertStub;
	jsb_ProductManager_class->finalize = js_eureekah_ProductManager_finalize;
	jsb_ProductManager_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	JSPropertySpec *properties = NULL;

	static JSFunctionSpec funcs[] = {
		JS_FN("restore", js_eureekah_ProductManager_restore, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("isProductPurchased", js_eureekah_ProductManager_isProductPurchased, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("buyProduct", js_eureekah_ProductManager_buyProduct, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getClassTypeInfo", js_eureekah_ProductManager_getClassTypeInfo, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("isBusy", js_eureekah_ProductManager_isBusy, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getProductPrice", js_eureekah_ProductManager_getProductPrice, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("ctor", js_eureekah_ProductManager_ctor, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	static JSFunctionSpec st_funcs[] = {
		JS_FN("sharedInstance", js_eureekah_ProductManager_sharedInstance, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};

	jsb_ProductManager_prototype = JS_InitClass(
		cx, global,
		NULL, // parent proto
		jsb_ProductManager_class,
		js_eureekah_ProductManager_constructor, 0, // constructor
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
	JSBool found;
	JS_SetPropertyAttributes(cx, global, "ProductManager", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<Eureekah::ProductManager> t;
	js_type_class_t *p;
	uint32_t typeId = t.s_id();
	HASH_FIND_INT(_js_global_type_ht, &typeId, p);
	if (!p) {
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->type = typeId;
		p->jsclass = jsb_ProductManager_class;
		p->proto = jsb_ProductManager_prototype;
		p->parentProto = NULL;
		HASH_ADD_INT(_js_global_type_ht, type, p);
	}
}


JSClass  *jsb_GoogleAnalytics_class;
JSObject *jsb_GoogleAnalytics_prototype;

JSBool js_eureekah_GoogleAnalytics_trackScreen(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	if (argc == 1) {
		const char* arg0;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		Eureekah::GoogleAnalytics::trackScreen(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}
	JS_ReportError(cx, "wrong number of arguments");
	return JS_FALSE;
}

JSBool js_eureekah_GoogleAnalytics_trackEvent(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	if (argc == 4) {
		const char* arg0;
		const char* arg1;
		const char* arg2;
		const char* arg3;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		std::string arg1_tmp; ok &= jsval_to_std_string(cx, argv[1], &arg1_tmp); arg1 = arg1_tmp.c_str();
		std::string arg2_tmp; ok &= jsval_to_std_string(cx, argv[2], &arg2_tmp); arg2 = arg2_tmp.c_str();
		std::string arg3_tmp; ok &= jsval_to_std_string(cx, argv[3], &arg3_tmp); arg3 = arg3_tmp.c_str();
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		Eureekah::GoogleAnalytics::trackEvent(arg0, arg1, arg2, arg3);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}
	JS_ReportError(cx, "wrong number of arguments");
	return JS_FALSE;
}

JSBool js_eureekah_GoogleAnalytics_setCustomDimensionForIndex(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	if (argc == 2) {
		int arg0;
		const char* arg1;
		ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
		std::string arg1_tmp; ok &= jsval_to_std_string(cx, argv[1], &arg1_tmp); arg1 = arg1_tmp.c_str();
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		Eureekah::GoogleAnalytics::setCustomDimensionForIndex(arg0, arg1);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}
	JS_ReportError(cx, "wrong number of arguments");
	return JS_FALSE;
}

JSBool js_eureekah_GoogleAnalytics_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		Eureekah::GoogleAnalytics* cobj = new Eureekah::GoogleAnalytics();
		TypeTest<Eureekah::GoogleAnalytics> t;
		js_type_class_t *typeClass;
		uint32_t typeId = t.s_id();
		HASH_FIND_INT(_js_global_type_ht, &typeId, typeClass);
		assert(typeClass);
		JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
		JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
		// link the native object with the javascript object
		js_proxy_t* p = jsb_new_proxy(cobj, obj);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}




void js_eureekah_GoogleAnalytics_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (GoogleAnalytics)", obj);
    js_proxy_t* nproxy;
    js_proxy_t* jsproxy;
    jsproxy = jsb_get_js_proxy(obj);
    if (jsproxy) {
        nproxy = jsb_get_native_proxy(jsproxy->ptr);

        Eureekah::GoogleAnalytics *nobj = static_cast<Eureekah::GoogleAnalytics *>(nproxy->ptr);
        if (nobj)
            delete nobj;
        
        jsb_remove_proxy(nproxy, jsproxy);
    }
}

static JSBool js_eureekah_GoogleAnalytics_ctor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
    Eureekah::GoogleAnalytics *nobj = new Eureekah::GoogleAnalytics();
    js_proxy_t* p = jsb_new_proxy(nobj, obj);
    JS_SET_RVAL(cx, vp, JSVAL_VOID);
    return JS_TRUE;
}

void js_register_eureekah_GoogleAnalytics(JSContext *cx, JSObject *global) {
	jsb_GoogleAnalytics_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_GoogleAnalytics_class->name = "GoogleAnalytics";
	jsb_GoogleAnalytics_class->addProperty = JS_PropertyStub;
	jsb_GoogleAnalytics_class->delProperty = JS_PropertyStub;
	jsb_GoogleAnalytics_class->getProperty = JS_PropertyStub;
	jsb_GoogleAnalytics_class->setProperty = JS_StrictPropertyStub;
	jsb_GoogleAnalytics_class->enumerate = JS_EnumerateStub;
	jsb_GoogleAnalytics_class->resolve = JS_ResolveStub;
	jsb_GoogleAnalytics_class->convert = JS_ConvertStub;
	jsb_GoogleAnalytics_class->finalize = js_eureekah_GoogleAnalytics_finalize;
	jsb_GoogleAnalytics_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	JSPropertySpec *properties = NULL;

	JSFunctionSpec *funcs = NULL;

	static JSFunctionSpec st_funcs[] = {
		JS_FN("trackScreen", js_eureekah_GoogleAnalytics_trackScreen, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("trackEvent", js_eureekah_GoogleAnalytics_trackEvent, 4, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setCustomDimensionForIndex", js_eureekah_GoogleAnalytics_setCustomDimensionForIndex, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};

	jsb_GoogleAnalytics_prototype = JS_InitClass(
		cx, global,
		NULL, // parent proto
		jsb_GoogleAnalytics_class,
		js_eureekah_GoogleAnalytics_constructor, 0, // constructor
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
	JSBool found;
	JS_SetPropertyAttributes(cx, global, "GoogleAnalytics", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<Eureekah::GoogleAnalytics> t;
	js_type_class_t *p;
	uint32_t typeId = t.s_id();
	HASH_FIND_INT(_js_global_type_ht, &typeId, p);
	if (!p) {
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->type = typeId;
		p->jsclass = jsb_GoogleAnalytics_class;
		p->proto = jsb_GoogleAnalytics_prototype;
		p->parentProto = NULL;
		HASH_ADD_INT(_js_global_type_ht, type, p);
	}
}

void register_all_eureekah(JSContext* cx, JSObject* obj) {
	// first, try to get the ns
	jsval nsval;
	JSObject *ns;
	JS_GetProperty(cx, obj, "ek", &nsval);
	if (nsval == JSVAL_VOID) {
		ns = JS_NewObject(cx, NULL, NULL, NULL);
		nsval = OBJECT_TO_JSVAL(ns);
		JS_SetProperty(cx, obj, "ek", &nsval);
	} else {
		JS_ValueToObject(cx, nsval, &ns);
	}
	obj = ns;

	js_register_eureekah_GoogleAnalytics(cx, obj);
	js_register_eureekah_ProductManager(cx, obj);
	js_register_eureekah_Utilities(cx, obj);
}

