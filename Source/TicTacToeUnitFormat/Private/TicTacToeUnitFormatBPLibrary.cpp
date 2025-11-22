// Copyright Epic Games, Inc. All Rights Reserved.

#include "TicTacToeUnitFormatBPLibrary.h"
#include "Kismet/KismetTextLibrary.h"
#include "TicTacToeUnitFormat.h"



//UTicTacToeUnitFormatBPLibrary::UTicTacToeUnitFormatBPLibrary(class FObjectInitializer const &)
//{
//}

double UTicTacToeUnitFormatBPLibrary::ConvertLength(float length, ELengthUnit fromUnit, ELengthUnit toUnit)
{
	if (!LengthConversionsToM.Contains(fromUnit)) return 0.0;
	if (!LengthConversionsToM.Contains(toUnit)) return 0.0;
	return ( length * LengthConversionsToM[fromUnit] ) / LengthConversionsToM[toUnit];
}

FText UTicTacToeUnitFormatBPLibrary::FormatLength(float length, ELengthUnit fromUnit, ELengthUnit toUnit, EAutoUnitType AutoUnit, bool UseExtendedAutoUnits, int precision, bool ForceSign, bool UseGrouping)
{
	if (!LengthConversionsToM.Contains(fromUnit)) return FText();
	
	// Convert incoming unit to meters
	double length_meters = length * LengthConversionsToM[fromUnit];

	ELengthUnit target_unit = toUnit;

	// Auto unit
	switch (AutoUnit)
	{
	case EAutoUnitType::AUT_OFF: break;
	case EAutoUnitType::AUT_MET_AUTO:
		if (length_meters < 0.01) {
			target_unit = ELengthUnit::LU_MET_MM;
			break;
		}
		if (length_meters < 1.0) {
			target_unit = ELengthUnit::LU_MET_CM;
			break;
		}
		if (length_meters < 1000.0) {
			target_unit = ELengthUnit::LU_MET_M;
			break;
		}
		target_unit = ELengthUnit::LU_MET_KM;
		break;
	case EAutoUnitType::AUT_IMP_US_AUTO:
		if (length_meters < 0.5) {
			target_unit = ELengthUnit::LU_US_INCH;
			break;
		}
		if (length_meters < 2.0) {
			target_unit = ELengthUnit::LU_US_FOOT;
			break;
		}
		if (length_meters < 500) {
			target_unit = ELengthUnit::LU_US_YARD;
			break;
		}
		target_unit = ELengthUnit::LU_US_MILE;
		break;

	default: break;
	}

	if ( !LengthConversionsToM.Contains(target_unit) ) return FText();
	if ( !LengthUnitDisplayStrings.Contains(target_unit) ) return FText();
	
	// Convert meters to target unit
	double length_converted = length_meters / LengthConversionsToM[target_unit];

	return FText::Format(
		FText::FromString("{0}{1}"),
		UKismetTextLibrary::Conv_DoubleToText(length_converted, ERoundingMode::HalfToEven, ForceSign, UseGrouping, 1, 324, 0, precision),
		LengthUnitDisplayStrings[target_unit]
	);
}

double UTicTacToeUnitFormatBPLibrary::ConvertWeight(float length, EWeightUnit fromUnit, EWeightUnit toUnit)
{
	if (!WeightConversionToKG.Contains(fromUnit)) return 0.0;
	if (!WeightConversionToKG.Contains(toUnit)) return 0.0;
	return ( length * WeightConversionToKG[fromUnit] ) / WeightConversionToKG[toUnit];
}

FText UTicTacToeUnitFormatBPLibrary::FormatWeight(float weight, EWeightUnit fromUnit, EWeightUnit toUnit, EAutoUnitType AutoUnit, bool UseExtendedAutoUnits, int precision, bool ForceSign, bool UseGrouping)
{
	if (!WeightConversionToKG.Contains(fromUnit)) return FText();

	// Convert incoming unit to meters
	double weight_kg = weight * WeightConversionToKG[fromUnit];

	EWeightUnit target_unit = toUnit;

	// Auto unit
	switch (AutoUnit)
	{
	case EAutoUnitType::AUT_OFF: break;
	case EAutoUnitType::AUT_MET_AUTO:
		if (weight_kg < 0.001) {
			target_unit = EWeightUnit::WU_MET_MG;
			break;
		}
		if (weight_kg < 0.1) {
			target_unit = EWeightUnit::WU_MET_G;
			break;
		}
		if (weight_kg < 1000.0) {
			target_unit = EWeightUnit::WU_MET_KG;
			break;
		}
		target_unit = EWeightUnit::WU_MET_TON;
		break;
	case EAutoUnitType::AUT_IMP_US_AUTO:
		if (weight_kg < 0.028) {
			target_unit = EWeightUnit::WU_US_GR;
			break;
		}
		if (weight_kg < 0.5) {
			target_unit = EWeightUnit::WU_US_OZ;
			break;
		}
		if (weight_kg < 1017) {
			target_unit = EWeightUnit::WU_US_LB;
			break;
		}
		target_unit = EWeightUnit::WU_US_TON_S;
		break;

	default: break;
	}

	if (!WeightConversionToKG.Contains(target_unit)) return FText();
	if (!WeightUnitDisplayStrings.Contains(target_unit)) return FText();

	// Convert meters to target unit
	double length_converted = weight_kg / WeightConversionToKG[target_unit];

	return FText::Format(
		FText::FromString("{0}{1}"),
		UKismetTextLibrary::Conv_DoubleToText(length_converted, ERoundingMode::HalfToEven, ForceSign, UseGrouping, 1, 324, 0, precision),
		WeightUnitDisplayStrings[target_unit]
	);
}

double UTicTacToeUnitFormatBPLibrary::ConvertVolume(float volume, EVolumeUnit fromUnit, EVolumeUnit toUnit)
{
	if (!VolumeConversionToM3.Contains(fromUnit)) return 0.0;
	if (!VolumeConversionToM3.Contains(toUnit)) return 0.0;

	return ( volume * VolumeConversionToM3[fromUnit] ) / VolumeConversionToM3[toUnit];
}

FText UTicTacToeUnitFormatBPLibrary::FormatVolume(float volume, EVolumeUnit fromUnit, EVolumeUnit toUnit, EAutoVolumeUnitType AutoUnit, bool UseExtendedAutoUnits, int precision, bool ForceSign, bool UseGrouping)
{
	if (!VolumeConversionToM3.Contains(fromUnit)) return FText();

	// Convert incoming unit to meters
	double volume_m3 = volume * VolumeConversionToM3[fromUnit];

	EVolumeUnit target_unit = toUnit;

	// Auto unit
	switch (AutoUnit)
	{
	case EAutoVolumeUnitType::AUT_OFF: break;
	case EAutoVolumeUnitType::AUT_MET_AUTO:
		if (volume_m3 < 0.0001) {
			target_unit = EVolumeUnit::VU_MET_MM3;
			break;
		}
		if (volume_m3 < 0.1) {
			target_unit = EVolumeUnit::VU_MET_CM3;
			break;
		}
		if (volume_m3 < 1000000) {
			target_unit = EVolumeUnit::VU_MET_M3;
			break;
		}
		if (volume_m3 < 1000000000.0 && UseExtendedAutoUnits ) {
			target_unit = EVolumeUnit::VU_MET_HM3;
			break;
		}
		target_unit = EVolumeUnit::VU_MET_KM3;
		break;
	case EAutoVolumeUnitType::AUT_IMP_AUTO:
		if (volume_m3 < 0.001) {
			target_unit = EVolumeUnit::VU_US_IN3;
			break;
		}
		if (volume_m3 < 0.5) {
			target_unit = EVolumeUnit::VU_US_FT3;
			break;
		}
		if (volume_m3 < 2000) {
			target_unit = EVolumeUnit::VU_US_YD3;
			break;
		}
		target_unit = EVolumeUnit::VU_US_ACREFT;
		break;

	default: break;
	}

	if (!VolumeConversionToM3.Contains(target_unit)) return FText();
	if (!VolumeUnitDisplayStrings.Contains(target_unit)) return FText();

	// Convert meters to target unit
	double volume_converted = volume_m3 / VolumeConversionToM3[target_unit];

	return FText::Format(
		FText::FromString("{0}{1}"),
		UKismetTextLibrary::Conv_DoubleToText(volume_converted, ERoundingMode::HalfToEven, ForceSign, UseGrouping, 1, 324, 0, precision),
		VolumeUnitDisplayStrings[target_unit]
	);
}

double UTicTacToeUnitFormatBPLibrary::ConvertArea(float volume, EAreaUnit fromUnit, EAreaUnit toUnit)
{
	if (!AreaConversionToM2.Contains(fromUnit)) return 0.0;
	if (!AreaConversionToM2.Contains(toUnit)) return 0.0;
	return ( volume * AreaConversionToM2[fromUnit] ) / AreaConversionToM2[toUnit];
}

FText UTicTacToeUnitFormatBPLibrary::FormatArea(float volume, EAreaUnit fromUnit, EAreaUnit toUnit, EAutoUnitType AutoUnit, bool UseExtendedAutoUnits, int precision, bool ForceSign, bool UseGrouping)
{
	if (!AreaConversionToM2.Contains(fromUnit)) return FText();

	// Convert incoming unit to meters
	double area_m2 = volume * AreaConversionToM2[fromUnit];

	EAreaUnit target_unit = toUnit;

	// Auto unit
	switch (AutoUnit)
	{
	case EAutoUnitType::AUT_OFF: break;
	case EAutoUnitType::AUT_MET_AUTO:
		if (area_m2 < 0.0001) {
			target_unit = EAreaUnit::AU_MET_MM2;
			break;
		}
		if (area_m2 < 0.1) {
			target_unit = EAreaUnit::AU_MET_CM2;
			break;
		}
		if (area_m2 < 10000.0) {
			target_unit = EAreaUnit::AU_MET_M2;
			break;
		}
		if (area_m2 < 100000000.0) {
			target_unit = EAreaUnit::AU_MET_HA;
			break;
		}
		target_unit = EAreaUnit::AU_MET_KM2;
		break;
	case EAutoUnitType::AUT_IMP_US_AUTO:
		if (area_m2 < 0.01) {
			target_unit = EAreaUnit::AU_US_SQIN;
			break;
		}
		if (area_m2 < 0.1) {
			target_unit = EAreaUnit::AU_US_SQFT;
			break;
		}
		if (area_m2 < 4000) {
			target_unit = EAreaUnit::AU_US_SQYD;
			break;
		}
		target_unit = EAreaUnit::AU_US_ACRE;
		break;

	default: break;
	}

	if (!AreaConversionToM2.Contains(target_unit)) return FText();
	if (!AreaUnitDisplayStrings.Contains(target_unit)) return FText();

	// Convert meters to target unit
	double area_converted = area_m2 / AreaConversionToM2[target_unit];

	return FText::Format(
		FText::FromString("{0}{1}"),
		UKismetTextLibrary::Conv_DoubleToText(area_converted, ERoundingMode::HalfToEven, ForceSign, UseGrouping, 1, 324, 0, precision),
		AreaUnitDisplayStrings[target_unit]
	);
}



