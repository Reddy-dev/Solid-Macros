// Elie Wiese-Namir © 2025. All Rights Reserved.

#include "SolidCppStructOps.h"

FSolidMoveableStructRegistry& FSolidMoveableStructRegistry::Get()
{
	static FSolidMoveableStructRegistry Instance;
	return Instance;
}

bool FSolidMoveableStructRegistry::IsStructMovable(const TSolidNotNull<const UScriptStruct*> InStruct) const
{
	return MoveableStructs.Contains(InStruct);
}

bool FSolidMoveableStructRegistry::IsStructMoveConstructible(const TSolidNotNull<const UScriptStruct*> InStruct) const
{
	return IsStructMovable(InStruct) && GetStructTypeHookInfo(InStruct).MoveConstructor != nullptr;
}

bool FSolidMoveableStructRegistry::IsStructMoveAssignable(const TSolidNotNull<const UScriptStruct*> InStruct) const
{
	return IsStructMovable(InStruct) && GetStructTypeHookInfo(InStruct).MoveAssignment != nullptr;
}

const FSolidMoveableStructRegistry::FStructTypeHookInfo& FSolidMoveableStructRegistry::GetStructTypeHookInfo(
	const TSolidNotNull<const UScriptStruct*> InStruct) const
{
	solid_checkf(IsStructMovable(InStruct), TEXT("InStruct is not registered as moveable!"));
	return MoveableStructs.FindChecked(InStruct);
}
