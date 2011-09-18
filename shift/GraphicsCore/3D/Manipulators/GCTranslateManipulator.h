#ifndef GCDISTANCEMANIPULATOR_H
#define GCDISTANCEMANIPULATOR_H

#include "GCManipulator.h"
#include "sbaseproperties.h"
#include "sbasepointerproperties.h"

class GCSingularTranslateManipulator : public GCLinearDragManipulator
  {
  S_PROPERTY_CONTAINER(GCSingularTranslateManipulator, GCLinearDragManipulator, 0);

public:
  GCSingularTranslateManipulator();

  void addDriven(TransformProperty *in);

  void onDrag(const MouseMoveEvent &);

private:
  QVector <TransformProperty *> _driven;
  };

class GCTranslateManipulator : public GCLinearDragManipulator
  {
  S_PROPERTY_CONTAINER(GCTranslateManipulator, GCVisualCompoundManipulator, 0);

public:
  GCTranslateManipulator();

  GCSingularTranslateManipulator central;

  void addDriven(TransformProperty *in);
  };

#endif // GCDISTANCEMANIPULATOR_H
