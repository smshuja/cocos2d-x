/*
 * JS Bindings: https://github.com/zynga/jsbindings
 *
 * Copyright (c) 2012 Zynga Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "js_bindings_config.h"
#include "js_bindings_core.h"
#include "jsfriendapi.h"
#include "jsb_opengl_manual.h"
#include "js_bindings_opengl.h"

//#include "jsb_opengl_functions_registration.h"

// system
#include "eureekah_manual_functions.h"

void register_eureekah_manual_functions(JSContext *cx, JSObject *obj)
{
	//
	// gl
	//
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
        
	// New WebGL functions, not present on OpenGL ES 2.0
	JS_DefineFunction(cx, ns, "_doesObjectExist", JSB_ekDoesObjectExist, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
}

