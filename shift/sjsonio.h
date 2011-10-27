#ifndef SJSONIO_H
#define SJSONIO_H

#include "QBuffer"
#include "sloader.h"
#include "QXmlStreamWriter"
#include "QXmlStreamReader"


class SHIFT_EXPORT SJSONSaver : private SSaver
  {
XProperties:
  XProperty(bool, autoWhitespace, setAutoWhitespace);

public:
  SJSONSaver();

  void writeToDevice(QIODevice *device, const SEntity *ent);

private:
  void setType(const SPropertyInformation *);

  void beginChildren(xsize);
  void endChildren();
  void beginNextChild();
  void endNextChild();

  void write(const SProperty *);

  void beginAttribute(const char *);
  void endAttribute(const char *);

  QIODevice *_device;
  const SEntity *_root;

  QVector <bool> _commaStack;

  QString _inAttribute;
  QBuffer _buffer;
  };

struct JSON_value_struct;
struct JSON_parser_struct;
class SHIFT_EXPORT SJSONLoader : private SLoader
  {
public:
  SJSONLoader();
  ~SJSONLoader();

  void readFromDevice(QIODevice *device, SEntity *parent);

private:
  const SPropertyInformation *type() const;

  xsize beginChildren() const;
  void endChildren() const;
  void beginNextChild();
  void endNextChild();

  void read(SPropertyContainer *);

  void beginAttribute(const char *);
  void endAttribute(const char *);

  virtual void resolveInputAfterLoad(SProperty *, const QString &);

  void readAllAttributes();
  void readNext() const;
  static int callback(void *ctx, int type, const JSON_value_struct* value);

  mutable bool _parseError;
  JSON_parser_struct* _jc;
  mutable QIODevice *_device;
  SEntity *_root;
  QHash <QString, QByteArray> _currentAttributes;
  QByteArray _currentValue;

  QByteArray _currentAttributeValue;


  enum State
    {
    Start,
    Attributes,
    AttributesEnd,
    Children,
    ChildrenEnd
    };

  mutable bool _readNext;
  State _current;
  QString _currentKey;

  mutable QString _scratch;

  QBuffer _buffer;

  QHash<SProperty *, QString> _resolveAfterLoad;
  };

#endif // SJSONIO_H