// Copyright Epic Games, Inc. All Rights Reserved.

#include "TicTacToeUnitFormatBPLibrary.h"
#include "Kismet/KismetTextLibrary.h"
#include "TicTacToeUnitFormat.h"



ELengthUnit UTicTacToeUnitFormatBPLibrary::GetAutoLength(double length_meters, EAutoUnitType AutoUnit)
{
	switch (AutoUnit)
	{
	case EAutoUnitType::AUT_OFF: break;
	case EAutoUnitType::AUT_MET_AUTO:
		if (length_meters < 0.01)	return ELengthUnit::LU_MET_MM;
		if (length_meters < 1.0)	return ELengthUnit::LU_MET_CM;
		if (length_meters < 1000.0)	return ELengthUnit::LU_MET_M;
		return ELengthUnit::LU_MET_KM;
	
	case EAutoUnitType::AUT_IMP_US_AUTO:
		if (length_meters < 0.5)	return ELengthUnit::LU_US_INCH;
		if (length_meters < 2.0)	return ELengthUnit::LU_US_FOOT;
		if (length_meters < 500)	return ELengthUnit::LU_US_YARD;
		return ELengthUnit::LU_US_MILE;

	default: return ELengthUnit::LU_MET_M;
	}
	return ELengthUnit::LU_MET_M;
}

EPressureUnit UTicTacToeUnitFormatBPLibrary::GetAutoPressure(double pressure_pascals, EAutoPressureUnitType AutoUnit)
{
	if (AutoUnit == EAutoPressureUnitType::AUT_MET_AUTO)
	{
		if (pressure_pascals < 0.1) return EPressureUnit::PU_MET_MPA;
		if (pressure_pascals < 1000.0) return EPressureUnit::PU_MET_PA;
		if (pressure_pascals < 1000000.0) return EPressureUnit::PU_MET_KPA;
		if (pressure_pascals < 1000000000.0) return EPressureUnit::PU_MET_MPA;
		return EPressureUnit::PU_MET_GPA;
	}
	return EPressureUnit::PU_MET_PA;
}

EEnergyUnit UTicTacToeUnitFormatBPLibrary::GetAutoEnergy(double energy_joules, EAutoEnergyUnitType AutoUnit)
{
	switch (AutoUnit)
	{
	default: return EEnergyUnit::EU_J;
		case EAutoEnergyUnitType::AUT_OFF: return EEnergyUnit::EU_J;
		case EAutoEnergyUnitType::AUT_WATTH:
		{
			if (energy_joules < 3600000.0) return EEnergyUnit::EU_WH;
			if (energy_joules < 3600000000.0) return EEnergyUnit::EU_KWH;
			return EEnergyUnit::EU_MWH;
		}
		case EAutoEnergyUnitType::AUT_JOULES:
		{
			if (energy_joules < 0.001) return EEnergyUnit::EU_UJ;
			if (energy_joules < 0.01) return EEnergyUnit::EU_MILIJ;
			if (energy_joules < 1000.0) return EEnergyUnit::EU_J;
			if (energy_joules < 1000000) return EEnergyUnit::EU_KJ;
			return EEnergyUnit::EU_MJ;
		}
	}
}

double UTicTacToeUnitFormatBPLibrary::ConvertLength(double length, ELengthUnit fromUnit, ELengthUnit toUnit)
{
	if (!LengthConversionsToM.Contains(fromUnit)) return 0.0;
	if (!LengthConversionsToM.Contains(toUnit)) return 0.0;
	return ( length * LengthConversionsToM[fromUnit] ) / LengthConversionsToM[toUnit];
}

FText UTicTacToeUnitFormatBPLibrary::FormatLength(double length, ELengthUnit fromUnit, ELengthUnit toUnit, EAutoUnitType AutoUnit, bool UseExtendedAutoUnits, int precision, bool ForceSign, bool UseGrouping)
{
	double length_meters = ConvertLength(length, fromUnit, ELengthUnit::LU_MET_M);

	ELengthUnit target_unit = toUnit;

	if (AutoUnit == EAutoUnitType::AUT_MET_AUTO || AutoUnit == EAutoUnitType::AUT_MET_AUTO)
		target_unit = GetAutoLength(length_meters, AutoUnit);

	double length_converted = ConvertLength(length_meters, ELengthUnit::LU_MET_M, toUnit);
	
	if ( !LengthUnitDisplayStrings.Contains(target_unit) ) return FText();

	return FText::Format(
		FText::FromString("{0}{1}"),
		UKismetTextLibrary::Conv_DoubleToText(length_converted, ERoundingMode::HalfToEven, ForceSign, UseGrouping, 1, 324, 0, precision),
		LengthUnitDisplayStrings[target_unit]
	);
}

double UTicTacToeUnitFormatBPLibrary::ConvertWeight(double length, EWeightUnit fromUnit, EWeightUnit toUnit)
{
	if (!WeightConversionToKG.Contains(fromUnit)) return 0.0;
	if (!WeightConversionToKG.Contains(toUnit)) return 0.0;
	return ( length * WeightConversionToKG[fromUnit] ) / WeightConversionToKG[toUnit];
}

FText UTicTacToeUnitFormatBPLibrary::FormatWeight(double weight, EWeightUnit fromUnit, EWeightUnit toUnit, EAutoUnitType AutoUnit, bool UseExtendedAutoUnits, int precision, bool ForceSign, bool UseGrouping)
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

double UTicTacToeUnitFormatBPLibrary::ConvertVolume(double volume, EVolumeUnit fromUnit, EVolumeUnit toUnit)
{
	if (!VolumeConversionToM3.Contains(fromUnit)) return 0.0;
	if (!VolumeConversionToM3.Contains(toUnit)) return 0.0;

	return ( volume * VolumeConversionToM3[fromUnit] ) / VolumeConversionToM3[toUnit];
}

FText UTicTacToeUnitFormatBPLibrary::FormatVolume(double volume, EVolumeUnit fromUnit, EVolumeUnit toUnit, EAutoVolumeUnitType AutoUnit, bool UseExtendedAutoUnits, int precision, bool ForceSign, bool UseGrouping)
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

double UTicTacToeUnitFormatBPLibrary::ConvertArea(double volume, EAreaUnit fromUnit, EAreaUnit toUnit)
{
	if (!AreaConversionToM2.Contains(fromUnit)) return 0.0;
	if (!AreaConversionToM2.Contains(toUnit)) return 0.0;
	return ( volume * AreaConversionToM2[fromUnit] ) / AreaConversionToM2[toUnit];
}

FText UTicTacToeUnitFormatBPLibrary::FormatArea(double volume, EAreaUnit fromUnit, EAreaUnit toUnit, EAutoUnitType AutoUnit, bool UseExtendedAutoUnits, int precision, bool ForceSign, bool UseGrouping)
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

double UTicTacToeUnitFormatBPLibrary::ConvertTemperature(double temperature, ETemperatureUnit fromUnit, ETemperatureUnit toUnit)
{
	double temp_k = 0.0;
	switch (fromUnit)
	{
		case ETemperatureUnit::TU_CEL:
			temp_k = temperature + 273.15;
			break;
		case ETemperatureUnit::TU_KEL:
			temp_k = temperature;
			break;
		case ETemperatureUnit::TU_FAR:
			temp_k = (temperature - 32.0) * 0.5555555555555 + 273.15;
	}
	switch (toUnit)
	{
		case ETemperatureUnit::TU_CEL:
			return temperature - 273.15;
		case ETemperatureUnit::TU_KEL:
			return temperature;
		case ETemperatureUnit::TU_FAR:
			return (temperature - 273.15) * 0.5555555555555 + 32;
		default:
			return 0.0;
	}
}

FText UTicTacToeUnitFormatBPLibrary::FormatTemperature(double temperature, ETemperatureUnit fromUnit, ETemperatureUnit toUnit, int precision, bool ForceSign, bool UseGrouping)
{
	if (!TemperatureUnitDisplayStrings.Contains(toUnit)) return FText();
	double temp_converted = ConvertTemperature(temperature, fromUnit, toUnit);
	return FText::Format(
		FText::FromString("{0}{1}"),
		UKismetTextLibrary::Conv_DoubleToText(temp_converted, ERoundingMode::HalfToEven, ForceSign, UseGrouping, 1, 324, 0, precision),
		TemperatureUnitDisplayStrings[toUnit]
	);
}

double UTicTacToeUnitFormatBPLibrary::ConvertTime(double time, ETimeUnit fromUnit, ETimeUnit toUnit)
{
	if (!TimeConversionToS.Contains(fromUnit)) return 0.0;
	if (!TimeConversionToS.Contains(toUnit)) return 0.0;
	return (time * TimeConversionToS[fromUnit]) / TimeConversionToS[toUnit];
}

FText UTicTacToeUnitFormatBPLibrary::FormatTime(double volume, ETimeUnit fromUnit, ETimeUnit toUnit, bool AutoUnit, int precision, bool ForceSign, bool UseGrouping)
{
	if (!TimeConversionToS.Contains(fromUnit)) return FText();

	// Convert incoming unit to meters
	double time_s = volume * TimeConversionToS[fromUnit];

	ETimeUnit target_unit = toUnit;

	// Auto unit
	if (AutoUnit)
	{
		if (time_s < 60.0)
			target_unit = ETimeUnit::TU_SEC;
		else if (time_s < 3600.0)
			target_unit = ETimeUnit::TU_MIN;
		else if (time_s < 86400.0)
			target_unit = ETimeUnit::TU_HR;
		else if (time_s < 2592000.0)
			target_unit = ETimeUnit::TU_MO;
		else
			target_unit = ETimeUnit::TU_YR;
	}

	if (!TimeConversionToS.Contains(target_unit)) return FText();
	if (!TimeUnitDisplayStrings.Contains(target_unit)) return FText();

	// Convert meters to target unit
	double time_converted = time_s / TimeConversionToS[target_unit];

	return FText::Format(
		FText::FromString("{0}{1}"),
		UKismetTextLibrary::Conv_DoubleToText(time_converted, ERoundingMode::HalfToEven, ForceSign, UseGrouping, 1, 324, 0, precision),
		TimeUnitDisplayStrings[target_unit]
	);
}

double UTicTacToeUnitFormatBPLibrary::ConvertSpeed(double speed, ELengthUnit fromLengthUnit, ELengthUnit toLengthUnit, ETimeUnit fromTimeUnit, ETimeUnit toTimeUnit)
{
	return ConvertLength(ConvertTime(speed, ETimeUnit::TU_SEC, toTimeUnit), fromLengthUnit, toLengthUnit);
}

FText UTicTacToeUnitFormatBPLibrary::FormatSpeed(double speed, ELengthUnit fromLengthUnit, ELengthUnit toLengthUnit, ETimeUnit fromTimeUnit, ETimeUnit toTimeUnit, EAutoUnitType AutoLengthUnit, bool UseExtendedAutoUnits, int precision, bool ForceSign, bool UseGrouping)
{
	ELengthUnit target_unit = toLengthUnit;
	
	double speed_converted = ConvertSpeed(speed, fromLengthUnit, ELengthUnit::LU_MET_M, fromTimeUnit, toTimeUnit);

	// Convert to m/time, determine best unit, then convert to that unit
	if (AutoLengthUnit == EAutoUnitType::AUT_MET_AUTO || AutoLengthUnit == EAutoUnitType::AUT_IMP_US_AUTO) {
		speed_converted = ConvertSpeed(speed, fromLengthUnit, ELengthUnit::LU_MET_M, fromTimeUnit, toTimeUnit);
		target_unit = GetAutoLength(speed_converted, AutoLengthUnit);
		speed_converted = ConvertSpeed(speed, fromLengthUnit, target_unit, fromTimeUnit, toTimeUnit);
	}
	
	if (!LengthUnitDisplayStrings.Contains(target_unit)) return FText();
	if (!TimeUnitDisplayStrings.Contains(toTimeUnit)) return FText();

	return FText::Format(
		FText::FromString("{0}{1}/{2}"),
		UKismetTextLibrary::Conv_DoubleToText(speed_converted, ERoundingMode::HalfToEven, ForceSign, UseGrouping, 1, 324, 0, precision),
		LengthUnitDisplayStrings[target_unit],
		TimeUnitDisplayStrings[toTimeUnit]
	);
}

double UTicTacToeUnitFormatBPLibrary::ConvertPressure(double pressure, EPressureUnit fromUnit, EPressureUnit toUnit)
{
	if (!PressureConversionToPa.Contains(fromUnit)) return 0.0;
	if (!PressureConversionToPa.Contains(toUnit)) return 0.0;
	return (pressure * PressureConversionToPa[fromUnit]) / PressureConversionToPa[toUnit];
}

FText UTicTacToeUnitFormatBPLibrary::FormatPressure(double pressure, EPressureUnit fromUnit, EPressureUnit toUnit, EAutoPressureUnitType AutoUnit, bool UseExtendedAutoUnits, int precision, bool ForceSign, bool UseGrouping)
{
	EPressureUnit target_unit = toUnit;

	if (AutoUnit == EAutoPressureUnitType::AUT_MET_AUTO) {
		double pressure_Pa = ConvertPressure(pressure, fromUnit, EPressureUnit::PU_MET_PA);
		target_unit = GetAutoPressure(pressure_Pa, AutoUnit);
	}

	double pressure_converted = ConvertPressure(pressure, fromUnit, target_unit);

	if (!PressureUnitDisplayStrings.Contains(target_unit)) return FText();

	return FText::Format(
		FText::FromString("{0}{1}"),
		UKismetTextLibrary::Conv_DoubleToText(pressure_converted, ERoundingMode::HalfToEven, ForceSign, UseGrouping, 1, 324, 0, precision),
		PressureUnitDisplayStrings[target_unit]
	);
}

double UTicTacToeUnitFormatBPLibrary::ConvertEnergy(double energy, EEnergyUnit fromUnit, EEnergyUnit toUnit)
{
	if (!EnergyConversionToJ.Contains(toUnit)) return 0.0;
	if (!EnergyConversionToJ.Contains(fromUnit)) return 0.0;
	return (energy * EnergyConversionToJ[fromUnit]) / EnergyConversionToJ[toUnit];
}

FText UTicTacToeUnitFormatBPLibrary::FormatEnergy(double energy, EEnergyUnit fromUnit, EEnergyUnit toUnit, EAutoEnergyUnitType AutoUnit, bool UseExtendedAutoUnits, int precision, bool ForceSign, bool UseGrouping)
{
	EEnergyUnit target_unit = toUnit;

	if (AutoUnit != EAutoEnergyUnitType::AUT_OFF) {
		double energy_j = ConvertEnergy(energy, fromUnit, EEnergyUnit::EU_J);
		target_unit = GetAutoEnergy(energy_j, AutoUnit);
	}

	double energy_converted = ConvertEnergy(energy, fromUnit, target_unit);

	if (!EnergyUnitDisplayStrings.Contains(target_unit)) return FText();

	return FText::Format(
		FText::FromString("{0}{1}"),
		UKismetTextLibrary::Conv_DoubleToText(energy_converted, ERoundingMode::HalfToEven, ForceSign, UseGrouping, 1, 324, 0, precision),
		EnergyUnitDisplayStrings[target_unit]
	);
}

double UTicTacToeUnitFormatBPLibrary::ConvertAngle(double angle, EAngleUnit fromUnit, EAngleUnit toUnit)
{
	if (!AngleConversionToDeg.Contains(toUnit)) return 0.0;
	if (!AngleConversionToDeg.Contains(fromUnit)) return 0.0;
	return (angle * AngleConversionToDeg[fromUnit]) / AngleConversionToDeg[toUnit];
}

FText UTicTacToeUnitFormatBPLibrary::FormatAngle(double angle, EAngleUnit fromUnit, EAngleUnit toUnit, int precision, bool ForceSign, bool UseGrouping)
{
	double angle_converted = ConvertAngle(angle, fromUnit, toUnit);

	if (!AngleUnitDisplayStrings.Contains(toUnit)) return FText();

	return FText::Format(
		FText::FromString("{0}{1}"),
		UKismetTextLibrary::Conv_DoubleToText(angle_converted, ERoundingMode::HalfToEven, ForceSign, UseGrouping, 1, 324, 0, precision),
		AngleUnitDisplayStrings[toUnit]
	);
}

