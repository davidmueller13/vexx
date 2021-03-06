#ifndef SXMLIO_H
#define SXMLIO_H

#include "QBuffer"
#include "sloader.h"
#include "QXmlStreamWriter"
#include "QXmlStreamReader"

class SHIFT_EXPORT SXMLSaver : private SSaver
  {
public:
  SXMLSaver();

  void writeToDevice(QIODevice *device, const SEntity *ent);

private:
  void setType(const SPropertyInformation *);

  void setChildCount(xsize);
  void beginNextChild();
  void endNextChild();

  void write(const SProperty *);

  void beginAttribute(const char *);
  void endAttribute(const char *);

  QXmlStreamWriter _writer;
  const SEntity *_root;

  QString _inAttribute;
  QBuffer _buffer;
  };

class SHIFT_EXPORT SXMLLoader : private SLoader
  {
public:
  SXMLLoader();

  void readFromDevice(QIODevice *device, SEntity *parent);

private:
  const SPropertyInformation *type() const;

  xsize childCount() const;
  void beginNextChild();
  void endNextChild();

  void read(SPropertyContainer *);

  void beginAttribute(const char *);
  void endAttribute(const char *);

  virtual void resolveInputAfterLoad(SProperty *, const QString &);

  void findNext(bool allowWhitespace);
  bool isValidElement() const;

  mutable QXmlStreamReader _reader;
  SEntity *_root;
  QXmlStreamAttributes _currentAttributes;
  QByteArray _currentValue;

  QByteArray _currentAttributeValue;
  QString _typeName;
  QString _childCount;

  bool _hasNextElement;
  mutable QString _scratch;

  QBuffer _buffer;

  QHash<SProperty *, QString> _resolveAfterLoad;
  };

#endif // SXMLIO_H
