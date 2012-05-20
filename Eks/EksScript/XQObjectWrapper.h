#ifndef XQOBJECTWRAPPER_H
#define XQOBJECTWRAPPER_H

#include "XUnorderedMap"
#include "XInterface.h"
#include "XScriptObject.h"
#include "XScriptEngine.h"
#include "QWidget"

class XQObjectConnectionList;

class EKSSCRIPT_EXPORT XQObjectWrapper
  {
public:
  static void initiate(XScriptEngine *);
  static XQObjectWrapper *instance();
  ~XQObjectWrapper();

  XScriptObject wrap(QObject *);
  XInterfaceBase *findInterface(const QMetaObject *object);

private:
  XQObjectWrapper();

  static void buildInterface(XInterfaceBase *interface, const QMetaObject *metaObject);

  XScriptEngine *_context;
  XUnorderedMap<const QMetaObject *, XInterfaceBase *> _objects;
  XUnorderedMap<QObject *, XQObjectConnectionList *> _connections;
  friend class XQObjectConnectionList;
  friend struct Utils;
  };

namespace XScriptConvert {
namespace internal {
template <> struct JSToNative<QObject> : XScriptConvert::internal::JSToNativeObject<QObject> {};

template <> struct NativeToJS<QObject>
  {
  XScriptValue operator()(QObject *n) const
    {
    return XQObjectWrapper::instance()->wrap(n);
    }
  XScriptValue operator()(QObject &n) const
    {
    xAssertFail();
    return this->operator()(&n);
    }
  };
}

template <> inline QWidget *castFromBase(QObject *ptr)
  {
  return qobject_cast<QWidget*>(ptr);
  }
}

namespace XScript
{
template <> class ClassCreator_Factory<QObject> : public ClassCreatorConvertableFactory<QObject, QObject> {};
}

#define X_SCRIPTABLE_QOBJECT_TYPE(type) X_SCRIPTABLE_TYPE_BASE_INHERITED(type, QObject) \
  namespace XScriptConvert { namespace internal { \
  template <> struct NativeToJS<type> : public NativeToJS<QObject> {}; } } \
  namespace XScript { \
  template <> class ClassCreator_Factory<type> : public ClassCreatorConvertableFactory<type, QObject> {}; }

X_SCRIPTABLE_QOBJECT_TYPE(QWidget)

#endif // XQOBJECTWRAPPER_H
