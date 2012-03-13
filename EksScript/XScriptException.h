#ifndef XSCRIPTEXCEPTION_H
#define XSCRIPTEXCEPTION_H

#include "QString"
#include "XScriptGlobal.h"
#include "v8.h"

EKSSCRIPT_EXPORT v8::Handle<v8::Value> TossAsError( const QString &err );
EKSSCRIPT_EXPORT v8::Handle<v8::Value> Toss(const QString &msg);

struct MissingThisException
  {
protected:
  QString msg;
  template <typename T>
  void init()
  {
    msg = QString("CastFromJS<%1>() returned NULL. Throwing to avoid dereferencing a NULL pointer!").arg(TypeName<T>::Value);
  }
  MissingThisException() {}

public:
  QString const &Buffer() const { return msg; }
  };

#endif // XSCRIPTEXCEPTION_H
