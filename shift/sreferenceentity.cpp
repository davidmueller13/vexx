#include "sreferenceentity.h"
#include "styperegistry.h"
#include "spropertyinformationhelpers.h"

S_IMPLEMENT_PROPERTY(SReferenceEntity, Shift)

void SReferenceEntity::createTypeInformation(SPropertyInformationTyped<SReferenceEntity> *,
                                             const SPropertyInformationCreateData &)
  {
  }

SReferenceEntity::SReferenceEntity()
  {
  }
