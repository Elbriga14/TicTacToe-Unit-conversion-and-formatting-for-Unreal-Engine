// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "TicTacToeUnitFormatBPLibrary.generated.h"

/* 
*	Function library class.
*	Each function in it is expected to be static and represents blueprint node that can be called in any blueprint.
*
*	When declaring function you can define metadata for the node. Key function specifiers will be BlueprintPure and BlueprintCallable.
*	BlueprintPure - means the function does not affect the owning object in any way and thus creates a node without Exec pins.
*	BlueprintCallable - makes a function which can be executed in Blueprints - Thus it has Exec pins.
*	DisplayName - full name of the node, shown when you mouse over the node and in the blueprint drop down menu.
*				Its lets you name the node using characters not allowed in C++ function names.
*	CompactNodeTitle - the word(s) that appear on the node.
*	Keywords -	the list of keywords that helps you to find node when you search for it using Blueprint drop-down menu. 
*				Good example is "Print String" node which you can find also by using keyword "log".
*	Category -	the category your node will be under in the Blueprint drop-down menu.
*
*	For more info on custom blueprint nodes visit documentation:
*	https://wiki.unrealengine.com/Custom_Blueprint_Node_Creation
*/



UENUM(BlueprintType)
enum class EAutoUnitType : uint8
{
	AUT_OFF					UMETA(DisplayName = "Off"),
	AUT_MET_AUTO			UMETA(DisplayName = "Auto metric"),
	AUT_IMP_US_AUTO			UMETA(DisplayName = "Auto imperial (US)"),
};

UENUM(BlueprintType)
enum class EAutoVolumeUnitType : uint8
{
	AUT_OFF					UMETA(DisplayName = "Off"),
	AUT_MET_AUTO			UMETA(DisplayName = "Auto metric"),
	AUT_MET_FLUID_AUTO		UMETA(DisplayName = "Auto metric fluid (liter)"),
	AUT_IMP_AUTO			UMETA(DisplayName = "Auto imperial (US)"),
	AUT_IMP_FLUID_AUTO		UMETA(DisplayName = "Auto imperial fluid (US)"),
};

UENUM(BlueprintType)
enum class EAutoPressureUnitType : uint8
{
	AUT_OFF					UMETA(DisplayName = "Off"),
	AUT_MET_AUTO			UMETA(DisplayName = "Auto metric"),
};


UENUM(BlueprintType)
enum class ELengthUnit : uint8
{
	// Metric
	LU_MET_MM				UMETA(DisplayName = "millimeter"),
	LU_MET_CM				UMETA(DisplayName = "centimeter"),
	LU_MET_DM				UMETA(DisplayName = "decimeter"),
	LU_MET_M				UMETA(DisplayName = "meter"),
	LU_MET_DAM				UMETA(DisplayName = "decameter"),
	LU_MET_HM				UMETA(DisplayName = "hectometer"),
	LU_MET_KM				UMETA(DisplayName = "kilometer"),
	// Imperial USA
	LU_US_TWIP				UMETA(DisplayName = "Twip (US)"),
	LU_US_MIL				UMETA(DisplayName = "Thousandth of an inch (US)"),
	LU_US_POINT				UMETA(DisplayName = "Point (US)"),
	LU_US_PICA				UMETA(DisplayName = "Pica (US)"),
	LU_US_INCH				UMETA(DisplayName = "Inch (US)"),
	LU_US_FOOT				UMETA(DisplayName = "Foot (US)"),
	LU_US_YARD				UMETA(DisplayName = "Yard (US)"),
	LU_US_MILE				UMETA(DisplayName = "Mile (US)"),
	LU_US_LEAGUE			UMETA(DisplayName = "League (US)"),
	// Imperial British
	LU_BRIT_THOU			UMETA(DisplayName = "Thousandth of an inch (British)"),
	LU_BRIT_BARLEYCORN		UMETA(DisplayName = "Barleycorn (British)"),
	LU_BRIT_IN				UMETA(DisplayName = "Inch (British)"),
	LU_BRIT_HH				UMETA(DisplayName = "Hand (British)"),
	LU_BRIT_FT				UMETA(DisplayName = "Foot (British)"),
	LU_BRIT_YD				UMETA(DisplayName = "Yard (British)"),
	LU_BRIT_CH				UMETA(DisplayName = "Chain (British)"),
	LU_BRIT_FUR				UMETA(DisplayName = "Furlong (British)"),
	LU_BRIT_MI				UMETA(DisplayName = "Mile (British)"),
	LU_BRIT_LEA				UMETA(DisplayName = "League (British)"),
	// Maritime british
	LU_BRIT_FTM				UMETA(DisplayName = "Fathom (British)"),
	LU_BRIT_CABLE			UMETA(DisplayName = "Cable (British)"),
	LU_BRIT_NMI				UMETA(DisplayName = "Nautical mile (British)"),
	// Other
};

UENUM(BlueprintType)
enum class EWeightUnit : uint8
{
	// Metric
	WU_MET_MG				UMETA(DisplayName = "milligram"),
	WU_MET_CG				UMETA(DisplayName = "centigram"),
	WU_MET_G				UMETA(DisplayName = "gram"),
	WU_MET_DG				UMETA(DisplayName = "decigram"),
	WU_MET_HG				UMETA(DisplayName = "hectogram"),
	WU_MET_KG				UMETA(DisplayName = "kilogram"),
	WU_MET_TON				UMETA(DisplayName = "Metric ton"),
	// Imperial US
	WU_US_GR				UMETA(DisplayName = "Grain (US)"),
	WU_US_DR				UMETA(DisplayName = "Dram (US)"),
	WU_US_OZ				UMETA(DisplayName = "Ounce (US)"),
	WU_US_LB				UMETA(DisplayName = "Pound (US)"),
	WU_US_CWT_S				UMETA(DisplayName = "Hundredweight (short) (US)"),
	WU_US_CWT_L				UMETA(DisplayName = "Hundredweight (long) (US)"),
	WU_US_TON_S				UMETA(DisplayName = "Imperial ton (short) (US)"),
	WU_US_TON_L				UMETA(DisplayName = "Imperial ton (long) (US)"),
	// Imperial British
	WU_BRIT_GR				UMETA(DisplayName = "Grain (British)"),
	WU_BRIT_DR				UMETA(DisplayName = "Drachm (British)"),
	WU_BRIT_OZ				UMETA(DisplayName = "Ounce (British)"),
	WU_BRIT_LB				UMETA(DisplayName = "Pound (British)"),
	WU_BRIT_ST				UMETA(DisplayName = "Stone (British)"),
	WU_BRIT_QR				UMETA(DisplayName = "Quarter (British)"),
	WU_BRIT_CWT				UMETA(DisplayName = "Hundredweight (British)"),
	WU_BRIT_TON				UMETA(DisplayName = "Imperial ton (British)"),
	// Other
	WU_BRIT_SLUG			UMETA(DisplayName = "Slug (British)"),
};

UENUM(BlueprintType)
enum class EVolumeUnit : uint8
{
	// Metric fluid
	VU_MET_ML				UMETA(DisplayName = "mililiter"),
	VU_MET_CL				UMETA(DisplayName = "centiliter"),
	VU_MET_DL				UMETA(DisplayName = "deciliter"),
	VU_MET_L				UMETA(DisplayName = "liter"),
	VU_MET_DAL				UMETA(DisplayName = "decaliter"),
	VU_MET_HL				UMETA(DisplayName = "hectoliter"),
	VU_MET_KL				UMETA(DisplayName = "kikoliter"),
	// Metric
	VU_MET_MM3				UMETA(DisplayName = "milimeter cube"),
	VU_MET_CM3				UMETA(DisplayName = "centimeter cube"),
	VU_MET_DM3				UMETA(DisplayName = "decimeter cube"),
	VU_MET_M3				UMETA(DisplayName = "meter cube"),
	VU_MET_DAM3				UMETA(DisplayName = "decameter cube"),
	VU_MET_HM3				UMETA(DisplayName = "hectometer cube"),
	VU_MET_KM3				UMETA(DisplayName = "kilometer cube"),
	// Imperial british liquid
	VU_BRIT_FLOZ			UMETA(DisplayName = "fluid ounce (British)"),
	VU_BRIT_GI				UMETA(DisplayName = "gill (British)"),
	VU_BRIT_PT				UMETA(DisplayName = "pint (British)"),
	VU_BRIT_QT				UMETA(DisplayName = "quart (British)"),
	VU_BRIT_GAL				UMETA(DisplayName = "galon (British)"),
	// Imperial US fluid
	VU_US_MIN				UMETA(DisplayName = "minim (US)"),
	VU_US_FLDR				UMETA(DisplayName = "fluid dram (US)"),
	VU_US_TSP				UMETA(DisplayName = "teaspoon (US)"),
	VU_US_TBSP				UMETA(DisplayName = "tablespoon (US)"),
	VU_US_FLOZ				UMETA(DisplayName = "fluid ounce (US)"),
	VU_US_JIG				UMETA(DisplayName = "shot (US)"),
	VU_US_GI				UMETA(DisplayName = "gill (US)"),
	VU_US_C					UMETA(DisplayName = "cup (US)"),
	VU_US_PT				UMETA(DisplayName = "pint (US)"),
	VU_US_QT				UMETA(DisplayName = "quart (US)"),
	VU_US_POT				UMETA(DisplayName = "pottle (US)"),
	VU_US_GAL				UMETA(DisplayName = "gallon (US)"),
	VU_US_BBL				UMETA(DisplayName = "barrel (US)"),
	VU_US_OILBBL			UMETA(DisplayName = "oil barrel (US)"),
	VU_US_HOGSHEAD			UMETA(DisplayName = "hogshead (US)"),
	// Imperial US
	VU_US_IN3				UMETA(DisplayName = "cubic inch (US)"),
	VU_US_FT3				UMETA(DisplayName = "cubic foot (US)"),
	VU_US_YD3				UMETA(DisplayName = "cubic yard (US)"),
	VU_US_ACREFT			UMETA(DisplayName = "acre-foot (US)"),
};

UENUM(BlueprintType)
enum class EAreaUnit : uint8
{
	// Metric
	AU_MET_MM2				UMETA(DisplayName = "millimeter squared"),
	AU_MET_CM2				UMETA(DisplayName = "centimeter squared"),
	AU_MET_DM2				UMETA(DisplayName = "decimeter squared"),
	AU_MET_M2				UMETA(DisplayName = "meter squared"),
	AU_MET_DAM2				UMETA(DisplayName = "decameter squared"),
	AU_MET_HM2				UMETA(DisplayName = "hectometer squared"),
	AU_MET_HA				UMETA(DisplayName = "hectare"),
	AU_MET_KM2				UMETA(DisplayName = "kilometer squared"),
	// Imperial US
	AU_US_SQIN				UMETA(DisplayName = "square inch (US)"),
	AU_US_SQFT				UMETA(DisplayName = "square foot (US)"),
	AU_US_SQYD				UMETA(DisplayName = "square yard (US)"),
	AU_US_SQCH				UMETA(DisplayName = "square chain (US)"),
	AU_US_ACRE				UMETA(DisplayName = "acre (US)"),
	AU_US_SEC				UMETA(DisplayName = "section (US)"),
	AU_US_TWP				UMETA(DisplayName = "survey township (US)"),
};

UENUM(BlueprintType)
enum class ETemperatureUnit : uint8
{
	TU_CEL					UMETA(DisplayName = "Celcius"),
	TU_FAR					UMETA(DisplayName = "Farenheit"),
	TU_KEL					UMETA(DisplayName = "Kelvin"),
};

UENUM(BlueprintType)
enum class ETimeUnit : uint8
{
	TU_SEC					UMETA(DisplayName = "Second"),
	TU_MIN					UMETA(DisplayName = "Minute"),
	TU_HR					UMETA(DisplayName = "Hour"),
	TU_DAY					UMETA(DisplayName = "Day"),
	TU_MO					UMETA(DisplayName = "Month"),
	TU_YR					UMETA(DisplayName = "Year"),
};

UENUM(BlueprintType)
enum class EPressureUnit : uint8
{
	// Metric
	PU_MET_MPA			UMETA(DisplayName = "deciascal"),
	PU_MET_CPA			UMETA(DisplayName = "centiascal"),
	PU_MET_DPA			UMETA(DisplayName = "decipascal"),
	PU_MET_PA			UMETA(DisplayName = "pascal"),
	PU_MET_DAPA			UMETA(DisplayName = "decapascal"),
	PU_MET_HPA			UMETA(DisplayName = "hectopascal"),
	PU_MET_KPA			UMETA(DisplayName = "kilopascal"),
	PU_MET_BAR			UMETA(DisplayName = "bar"),
	PU_MET_MPA			UMETA(DisplayName = "megapascal"),
	PU_MET_GPA			UMETA(DisplayName = "gigapascal"),
	// Imperial (US)
	PU_MET_PSI			UMETA(DisplayName = "PSI"),
};

UCLASS()
class UTicTacToeUnitFormatBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

#define LOCTEXT_NAMESPACE "FTicTacToeUnitFormatModule"

	// --- --- LENGTH --- --- //

	inline static const TMap<ELengthUnit, double> LengthConversionsToM =
	{
		// Metric
		{ ELengthUnit::LU_MET_MM			, 0.001			},
		{ ELengthUnit::LU_MET_CM			, 0.01			},
		{ ELengthUnit::LU_MET_DM			, 0.1			},
		{ ELengthUnit::LU_MET_M				, 1.0			},
		{ ELengthUnit::LU_MET_DAM			, 10.0			},
		{ ELengthUnit::LU_MET_HM			, 100.0			},
		{ ELengthUnit::LU_MET_KM			, 1000.0		},

		// Imperial USA
		{ ELengthUnit::LU_US_TWIP			, 0.0000017638	},
		{ ELengthUnit::LU_US_MIL			, 0.00000254	},					
		{ ELengthUnit::LU_US_POINT			, 0.00003527	},
		{ ELengthUnit::LU_US_PICA			, 0.00423		},				
		{ ELengthUnit::LU_US_INCH			, 0.0254		},
		{ ELengthUnit::LU_US_FOOT			, 0.3048		},				
		{ ELengthUnit::LU_US_YARD			, 0.9144		},				
		{ ELengthUnit::LU_US_MILE			, 1609.344		},				
		{ ELengthUnit::LU_US_LEAGUE			, 4828.032		},		
		// Imperial British
		{ ELengthUnit::LU_BRIT_THOU			, 0.00000254	},
		{ ELengthUnit::LU_BRIT_BARLEYCORN	, 0.00846		},
		{ ELengthUnit::LU_BRIT_IN			, 0.0254		},
		{ ELengthUnit::LU_BRIT_HH			, 0.1016		},
		{ ELengthUnit::LU_BRIT_FT			, 0.3048		},
		{ ELengthUnit::LU_BRIT_YD			, 0.9144		},
		{ ELengthUnit::LU_BRIT_CH			, 20.1168		},
		{ ELengthUnit::LU_BRIT_FUR			, 201.168		},
		{ ELengthUnit::LU_BRIT_MI			, 1609.344		},
		{ ELengthUnit::LU_BRIT_LEA			, 4828.032		},
		// Maritime British
		{ ELengthUnit::LU_BRIT_FTM			, 1.852			},
		{ ELengthUnit::LU_BRIT_CABLE		, 185.2			},
		{ ELengthUnit::LU_BRIT_NMI			, 1852.0		},
	};

	inline static const TMap<ELengthUnit, FText> LengthUnitDisplayStrings =
	{
		// Metric
		{ ELengthUnit::LU_MET_MM			, LOCTEXT("mm"		,	"mm")	},
		{ ELengthUnit::LU_MET_CM			, LOCTEXT("cm"		,	"cm")	},
		{ ELengthUnit::LU_MET_DM			, LOCTEXT("dm"		,	"dm")	},
		{ ELengthUnit::LU_MET_M				, LOCTEXT("m"		,	"m")	},
		{ ELengthUnit::LU_MET_DAM			, LOCTEXT("dam"		,	"dam")	},
		{ ELengthUnit::LU_MET_HM			, LOCTEXT("Hm"		,	"Hm")	},
		{ ELengthUnit::LU_MET_KM			, LOCTEXT("Km"		,	"Km")	},
		// Imperial British
		{ ELengthUnit::LU_BRIT_THOU			, LOCTEXT("th"		,	"th")	},
		{ ELengthUnit::LU_BRIT_BARLEYCORN	, LOCTEXT("BCorn"	,	"BCorn")	},
		{ ELengthUnit::LU_BRIT_IN			, LOCTEXT("in"		,	"in")	},
		{ ELengthUnit::LU_BRIT_HH			, LOCTEXT("hh"		,	"hh")	},
		{ ELengthUnit::LU_BRIT_FT			, LOCTEXT("ft"		,	"ft")	},
		{ ELengthUnit::LU_BRIT_YD			, LOCTEXT("yd"		,	"yd")	},
		{ ELengthUnit::LU_BRIT_CH			, LOCTEXT("ch"		,	"ch")	},
		{ ELengthUnit::LU_BRIT_FUR			, LOCTEXT("fur"		,	"fur")	},
		{ ELengthUnit::LU_BRIT_MI			, LOCTEXT("mi"		,	"mi")	},
		{ ELengthUnit::LU_BRIT_LEA			, LOCTEXT("lea"		,	"lea")	},
		// Maritime
		{ ELengthUnit::LU_BRIT_FTM			, LOCTEXT("ftm"		,	"ftm")	},
		{ ELengthUnit::LU_BRIT_CABLE		, LOCTEXT("cable"	,	"cable")	},
		{ ELengthUnit::LU_BRIT_NMI			, LOCTEXT("nmi"		,	"nmi")	},
	};

	// --- --- WEIGHT --- --- //

	inline static const TMap<EWeightUnit, double> WeightConversionToKG =
	{
		// Metric
		{ EWeightUnit::WU_MET_MG			, 0.00001				},
		{ EWeightUnit::WU_MET_CG			, 0.0001				},
		{ EWeightUnit::WU_MET_G				, 0.001					},
		{ EWeightUnit::WU_MET_DG			, 0.01					},
		{ EWeightUnit::WU_MET_HG			, 0.1					},
		{ EWeightUnit::WU_MET_KG			, 1.0					},
		{ EWeightUnit::WU_MET_TON			, 1000.0				},
		// Imperial US
		{ EWeightUnit::WU_US_GR				, 0.0006479891			},
		{ EWeightUnit::WU_US_DR				, 0.0017718451953125	},
		{ EWeightUnit::WU_US_OZ				, 0.028349523125		},
		{ EWeightUnit::WU_US_LB				, 0.45359237			},
		{ EWeightUnit::WU_US_CWT_S			, 45.359237				},
		{ EWeightUnit::WU_US_CWT_L			, 50.80234544			},
		{ EWeightUnit::WU_US_TON_S			, 907.18474				},
		{ EWeightUnit::WU_US_TON_L			, 1016.0469088			},
		// Imperial British
		{ EWeightUnit::WU_BRIT_GR			, 0.0006479891			},
		{ EWeightUnit::WU_BRIT_DR			, 0.0017718451953125	},
		{ EWeightUnit::WU_BRIT_OZ			, 0.028349523125		},
		{ EWeightUnit::WU_BRIT_LB			, 0.45359237			},
		{ EWeightUnit::WU_BRIT_ST			, 6.35029318			},
		{ EWeightUnit::WU_BRIT_QR			, 12.70058636			},
		{ EWeightUnit::WU_BRIT_CWT			, 50.80234544			},
		{ EWeightUnit::WU_BRIT_TON			, 1016.0469088			},
		// Other
		{ EWeightUnit::WU_BRIT_SLUG			, 14.59390294			},
	};

	inline static const TMap<EWeightUnit, FText> WeightUnitDisplayStrings =
	{
		// Metric
		{ EWeightUnit::WU_MET_MG			, LOCTEXT("mg"		,	"mg")		},
		{ EWeightUnit::WU_MET_CG			, LOCTEXT("cg"		,	"cg")		},
		{ EWeightUnit::WU_MET_G				, LOCTEXT("g"		,	"g")		},
		{ EWeightUnit::WU_MET_DG			, LOCTEXT("dg"		,	"dg")		},
		{ EWeightUnit::WU_MET_HG			, LOCTEXT("hg"		,	"hg")		},
		{ EWeightUnit::WU_MET_KG			, LOCTEXT("kg"		,	"kg")		},
		{ EWeightUnit::WU_MET_TON			, LOCTEXT("t"		,	"t")		},
		// Imperial US
		{ EWeightUnit::WU_US_GR				, LOCTEXT("gr"		,	"gr")		},
		{ EWeightUnit::WU_US_DR				, LOCTEXT("dr"		,	"dr")		},
		{ EWeightUnit::WU_US_OZ				, LOCTEXT("oz"		,	"oz")		},
		{ EWeightUnit::WU_US_LB				, LOCTEXT("lb"		,	"lb")		},
		{ EWeightUnit::WU_US_CWT_S			, LOCTEXT("cwt"		,	"cwt")		},
		{ EWeightUnit::WU_US_CWT_L			, LOCTEXT("cwt"		,	"cwt")		},
		{ EWeightUnit::WU_US_TON_S			, LOCTEXT("ton"		,	"ton")		},
		{ EWeightUnit::WU_US_TON_L			, LOCTEXT("ton"		,	"ton")		},
		// Imperial British
		{ EWeightUnit::WU_BRIT_GR			, LOCTEXT("gr"		,	"gr")		},
		{ EWeightUnit::WU_BRIT_DR			, LOCTEXT("dr"		,	"dr")		},
		{ EWeightUnit::WU_BRIT_OZ			, LOCTEXT("oz"		,	"oz")		},
		{ EWeightUnit::WU_BRIT_LB			, LOCTEXT("lb"		,	"lb")		},
		{ EWeightUnit::WU_BRIT_ST			, LOCTEXT("st"		,	"st")		},
		{ EWeightUnit::WU_BRIT_QR			, LOCTEXT("qr"		,	"qr")		},
		{ EWeightUnit::WU_BRIT_CWT			, LOCTEXT("cwt"		,	"cwt")		},
		{ EWeightUnit::WU_BRIT_TON			, LOCTEXT("ton"		,	"ton")		},
		// Other
		{ EWeightUnit::WU_BRIT_SLUG			, LOCTEXT("slug"	,	"slug")		},
	};
	
	// --- --- VOLUME --- --- //

	inline static const TMap<EVolumeUnit, double> VolumeConversionToM3 =
	{
		// Metric fluid
		{ EVolumeUnit::VU_MET_ML			, 0.000001					},
		{ EVolumeUnit::VU_MET_CL			, 0.00001					},
		{ EVolumeUnit::VU_MET_DL			, 0.0001					},
		{ EVolumeUnit::VU_MET_L				, 0.001						},
		{ EVolumeUnit::VU_MET_DAL			, 0.010						},
		{ EVolumeUnit::VU_MET_HL			, 0.1						},
		{ EVolumeUnit::VU_MET_KL			, 1.0						},
		// Metric
		{ EVolumeUnit::VU_MET_MM3			, 0.000000001				},
		{ EVolumeUnit::VU_MET_CM3			, 0.000001					},
		{ EVolumeUnit::VU_MET_DM3			, 0.001						},
		{ EVolumeUnit::VU_MET_M3			, 1.0						},
		{ EVolumeUnit::VU_MET_DAM3			, 1000.0					},
		{ EVolumeUnit::VU_MET_HM3			, 1000000.0					},
		{ EVolumeUnit::VU_MET_KM3			, 1000000000.0				},
		// Imperial british fluid
		{ EVolumeUnit::VU_BRIT_FLOZ			, 0.000029574				},
		{ EVolumeUnit::VU_BRIT_GI			, 0.000118294				},
		{ EVolumeUnit::VU_BRIT_PT			, 0.000473176				},
		{ EVolumeUnit::VU_BRIT_QT			, 0.0011365225				},
		{ EVolumeUnit::VU_BRIT_GAL			, 0.00454609				},
		// Imperial US fluid
		{ EVolumeUnit::VU_US_MIN			, 0.000000061611519921875	},
		{ EVolumeUnit::VU_US_FLDR			, 0.0000036966911953125		},
		{ EVolumeUnit::VU_US_TSP			, 0.00000492892159375		},
		{ EVolumeUnit::VU_US_TBSP			, 0.00001478676478125		},
		{ EVolumeUnit::VU_US_FLOZ			, 0.0000295735295625		},
		{ EVolumeUnit::VU_US_JIG			, 0.00004436029434375		},
		{ EVolumeUnit::VU_US_GI				, 0.00011829411825			},
		{ EVolumeUnit::VU_US_C				, 0.0002365882365			},
		{ EVolumeUnit::VU_US_PT				, 0.0004731764773			},
		{ EVolumeUnit::VU_US_QT				, 0.000946352946			},
		{ EVolumeUnit::VU_US_POT			, 0.001892705892			},
		{ EVolumeUnit::VU_US_GAL			, 0.003785411784			},
		{ EVolumeUnit::VU_US_BBL			, 0.119240471196			},
		{ EVolumeUnit::VU_US_OILBBL			, 0.158987294928			},
		{ EVolumeUnit::VU_US_HOGSHEAD		, 0.238480942392			},
		// Imperial US
		{ EVolumeUnit::VU_US_IN3			, 0.000016387064			},
		{ EVolumeUnit::VU_US_FT3			, 0.028316846592			},
		{ EVolumeUnit::VU_US_YD3			, 0.764554857984			},
		{ EVolumeUnit::VU_US_ACREFT			, 1233.482					},
	};

	inline static const TMap<EVolumeUnit, FText> VolumeUnitDisplayStrings =
	{
		// Metric liters
		{ EVolumeUnit::VU_MET_ML			, LOCTEXT("met_mL"		, "mL")			},
		{ EVolumeUnit::VU_MET_CL			, LOCTEXT("met_cL"		, "cL")			},
		{ EVolumeUnit::VU_MET_DL			, LOCTEXT("met_dL"		, "dL")			},
		{ EVolumeUnit::VU_MET_L				, LOCTEXT("met_L"		, "L")			},
		{ EVolumeUnit::VU_MET_DAL			, LOCTEXT("met_DaL"		, "DaL")		},
		{ EVolumeUnit::VU_MET_HL			, LOCTEXT("met_hL"		, "hL")			},
		{ EVolumeUnit::VU_MET_KL			, LOCTEXT("met_kL"		, "kL")			},
		// Metric											
		{ EVolumeUnit::VU_MET_MM3			, LOCTEXT("met_mm3"		, "mm3")		},
		{ EVolumeUnit::VU_MET_CM3			, LOCTEXT("met_cm3"		, "cm3")		},
		{ EVolumeUnit::VU_MET_DM3			, LOCTEXT("met_dm3"		, "dm3")		},
		{ EVolumeUnit::VU_MET_M3			, LOCTEXT("met_m3"		, "m3")			},
		{ EVolumeUnit::VU_MET_DAM3			, LOCTEXT("met_Dam3"	, "Dam3")		},
		{ EVolumeUnit::VU_MET_HM3			, LOCTEXT("met_hm3"		, "hm3")		},
		{ EVolumeUnit::VU_MET_KM3			, LOCTEXT("met_km3"		, "km3")		},
		// Imperial	
		{ EVolumeUnit::VU_BRIT_FLOZ			, LOCTEXT("brit_fl oz"	, "fl oz")		},
		{ EVolumeUnit::VU_BRIT_GI			, LOCTEXT("brit_gi"		, "gi")			},
		{ EVolumeUnit::VU_BRIT_PT			, LOCTEXT("brit_pt"		, "pt")			},
		{ EVolumeUnit::VU_BRIT_QT			, LOCTEXT("brit_qt"		, "qt")			},
		{ EVolumeUnit::VU_BRIT_GAL			, LOCTEXT("brit_gal"	, "gal")		},
		// Imperial US fluid
		{ EVolumeUnit::VU_US_MIN			, LOCTEXT("us_min"		, "min"		)	},
		{ EVolumeUnit::VU_US_FLDR			, LOCTEXT("us_fl dr"	, "fl dr"	)	},
		{ EVolumeUnit::VU_US_TSP			, LOCTEXT("us_tsp"		, "tsp"		)	},
		{ EVolumeUnit::VU_US_TBSP			, LOCTEXT("us_tbsp"		, "tbsp"	)	},
		{ EVolumeUnit::VU_US_FLOZ			, LOCTEXT("us_fl oz"	, "fl oz"	)	},
		{ EVolumeUnit::VU_US_JIG			, LOCTEXT("us_jig"		, "jig"		)	},
		{ EVolumeUnit::VU_US_GI				, LOCTEXT("us_gi"		, "gi"		)	},
		{ EVolumeUnit::VU_US_C				, LOCTEXT("us_c"		, "c"		)	},
		{ EVolumeUnit::VU_US_PT				, LOCTEXT("us_pint"		, "pint"	)	},
		{ EVolumeUnit::VU_US_QT				, LOCTEXT("us_qt"		, "qt"		)	},
		{ EVolumeUnit::VU_US_POT			, LOCTEXT("us_pot"		, "pot"		)	},
		{ EVolumeUnit::VU_US_GAL			, LOCTEXT("us_gal"		, "gal"		)	},
		{ EVolumeUnit::VU_US_BBL			, LOCTEXT("us_bbl"		, "bbl"		)	},
		{ EVolumeUnit::VU_US_OILBBL			, LOCTEXT("us_oilbbl"	, "bbl"		)	},
		{ EVolumeUnit::VU_US_HOGSHEAD		, LOCTEXT("us_hogshead"	, "hogshead")	},
		// Imperial US	
		{ EVolumeUnit::VU_US_IN3			, LOCTEXT("us_in3"		, "in3")		},
		{ EVolumeUnit::VU_US_FT3			, LOCTEXT("us_ft3"		, "ft3")		},
		{ EVolumeUnit::VU_US_YD3			, LOCTEXT("us_yd3"		, "yd3")		},
		{ EVolumeUnit::VU_US_ACREFT			, LOCTEXT("us_acrefoot"	, "acre-foot")	},
	};

	// --- --- AREA --- --- //

	inline static const TMap<EAreaUnit, double> AreaConversionToM2 =
	{
		// Metric
		{ EAreaUnit::AU_MET_MM2				, 0.000001			},
		{ EAreaUnit::AU_MET_CM2				, 0.0001			},
		{ EAreaUnit::AU_MET_DM2				, 0.01				},
		{ EAreaUnit::AU_MET_M2				, 1.0				},
		{ EAreaUnit::AU_MET_DAM2			, 100.0				},
		{ EAreaUnit::AU_MET_HM2				, 10000.0			},
		{ EAreaUnit::AU_MET_HA				, 1000000.0			},
		{ EAreaUnit::AU_MET_KM2				, 100000000.0		},
		// Imperial US						  
		{ EAreaUnit::AU_US_SQIN				, 0.00064516		},
		{ EAreaUnit::AU_US_SQFT				, 0.09290304		},
		{ EAreaUnit::AU_US_SQYD				, 0.83612736		},
		{ EAreaUnit::AU_US_SQCH				, 404.68564224		},
		{ EAreaUnit::AU_US_ACRE				, 4046.8564224		},
		{ EAreaUnit::AU_US_SEC				, 258999800.0		},
		{ EAreaUnit::AU_US_TWP				, 9323993000.0		},
	};

	inline static const TMap<EAreaUnit, FText> AreaUnitDisplayStrings =
	{
		// Metric
		{ EAreaUnit::AU_MET_MM2				, LOCTEXT(	"met_mm2",	"mm2"	)	},
		{ EAreaUnit::AU_MET_CM2				, LOCTEXT(	"met_cm2",	"cm2"	)	},
		{ EAreaUnit::AU_MET_DM2				, LOCTEXT(	"met_dm2",	"dm2"	)	},
		{ EAreaUnit::AU_MET_M2				, LOCTEXT(	"met_m2",	"m2"	)	},
		{ EAreaUnit::AU_MET_DAM2			, LOCTEXT(	"met_dam2",	"Dam2"	)	},
		{ EAreaUnit::AU_MET_HM2				, LOCTEXT(	"met_hm2",	"hm2"	)	},
		{ EAreaUnit::AU_MET_HA				, LOCTEXT(	"met_ha",	"ha"	)	},
		{ EAreaUnit::AU_MET_KM2				, LOCTEXT(	"met_km2",	"km2"	)	},
		// Imperial US						  
		{ EAreaUnit::AU_US_SQIN				, LOCTEXT(	"us_sqin",	"sq in")	},
		{ EAreaUnit::AU_US_SQFT				, LOCTEXT(	"us_sqft",	"sq ft")	},
		{ EAreaUnit::AU_US_SQYD				, LOCTEXT(	"us_sqyd",	"sq yd")	},
		{ EAreaUnit::AU_US_SQCH				, LOCTEXT(	"us_sq ch",	"sq ch")	},
		{ EAreaUnit::AU_US_ACRE				, LOCTEXT(	"us_acre",	"acre")		},
		{ EAreaUnit::AU_US_SEC				, LOCTEXT(	"us_sec",	"sec")		},
		{ EAreaUnit::AU_US_TWP				, LOCTEXT(	"us_twp",	"twp")		},
	};

	// --- --- TEMPERATURE --- --- //

	inline static const TMap<ETemperatureUnit, FText> TemperatureUnitDisplayStrings =
	{
		{ ETemperatureUnit::TU_CEL			, LOCTEXT("cel",		"°C")		},
		{ ETemperatureUnit::TU_FAR			, LOCTEXT("far",		"°F")		},
		{ ETemperatureUnit::TU_KEL			, LOCTEXT("kel",		"K")		},
	};


	// --- --- TIME --- --- //

	inline static const TMap<ETimeUnit, double> TimeConversionToS =
	{
		{ ETimeUnit::TU_SEC	,	1.0										},
		{ ETimeUnit::TU_MIN	,	0.01666666666666666666666666666667		},
		{ ETimeUnit::TU_HR	,	2.7777777777777777777777777777778e-4	},
		{ ETimeUnit::TU_DAY	,	1.1574074074074074074074074074074e-5	},
		{ ETimeUnit::TU_MO	,	3.858024691358024691358024691358e-7		},
		{ ETimeUnit::TU_YR	,	3.1709791983764586504312531709792e-8	},
	};

	inline static const TMap<ETimeUnit, FText> TimeUnitDisplayStrings =
	{
		// Metric
		{ ETimeUnit::TU_SEC	,	LOCTEXT( "second"	, "s" )			},
		{ ETimeUnit::TU_MIN	,	LOCTEXT( "minute"	, "m" )			},
		{ ETimeUnit::TU_HR	,	LOCTEXT( "hour"		, "h" )			},
		{ ETimeUnit::TU_DAY	,	LOCTEXT( "day"		, "d" )			},
		{ ETimeUnit::TU_MO	,	LOCTEXT( "month"	, "m" )			},
		{ ETimeUnit::TU_YR	,	LOCTEXT( "year"		, "y" )			},
	};

	// --- --- PRESSURE --- --- //

	inline static const TMap<EPressureUnit, double> PressureConversionToPa =
	{
		{ EPressureUnit::PU_MET_MPA			, 0.001					},
		{ EPressureUnit::PU_MET_CPA			, 0.01					},
		{ EPressureUnit::PU_MET_DPA			, 0.1					},
		{ EPressureUnit::PU_MET_PA			, 1.0					},
		{ EPressureUnit::PU_MET_DAPA		, 10.0					},
		{ EPressureUnit::PU_MET_HPA			, 100.0					},
		{ EPressureUnit::PU_MET_KPA			, 1000.0				},
		{ EPressureUnit::PU_MET_BAR			, 100000.0				},
		{ EPressureUnit::PU_MET_MPA			, 1000000.0				},
		{ EPressureUnit::PU_MET_GPA			, 1000000000.0			},
		// Imperial (US)
		{ EPressureUnit::PU_MET_PSI			, 6894.757				},
	};

	inline static const TMap<EPressureUnit, FText> PressureUnitDisplayStrings =
	{
		{ EPressureUnit::PU_MET_MPA			, LOCTEXT("met_mPa", "mPa")		},
		{ EPressureUnit::PU_MET_CPA			, LOCTEXT("met_cPa", "cPa")		},
		{ EPressureUnit::PU_MET_DPA			, LOCTEXT("met_dPa", "dPa")		},
		{ EPressureUnit::PU_MET_PA			, LOCTEXT("met_Pa", "Pa")		},
		{ EPressureUnit::PU_MET_DAPA		, LOCTEXT("met_daPa", "daPa")	},
		{ EPressureUnit::PU_MET_HPA			, LOCTEXT("met_hPa", "hPa")		},
		{ EPressureUnit::PU_MET_KPA			, LOCTEXT("met_kPa", "kPa")		},
		{ EPressureUnit::PU_MET_BAR			, LOCTEXT("met_bar", "bar")		},
		{ EPressureUnit::PU_MET_MPA			, LOCTEXT("met_MPa", "MPa")		},
		{ EPressureUnit::PU_MET_GPA			, LOCTEXT("met_GPa", "GPa")		},
		// Imperial (US)
		{ EPressureUnit::PU_MET_PSI			, LOCTEXT("us_psi", "PSI")		},
	};

#undef LOCTEXT_NAMESPACE


	static ELengthUnit GetAutoLength(double length_meters, EAutoUnitType AutoUnit);

	static EPressureUnit GetAutoPressure(double pressure_pascals, EAutoPressureUnitType AutoUnit);

public:
	
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (Keywords = "TicTac"), Category = "TicTacToe UnitFormat")
	static double ConvertLength(float length, ELengthUnit fromUnit = ELengthUnit::LU_MET_CM, ELengthUnit toUnit = ELengthUnit::LU_MET_CM);

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (Keywords = "TicTac"), Category = "TicTacToe UnitFormat")
	static FText FormatLength(float length, ELengthUnit fromUnit=ELengthUnit::LU_MET_CM, ELengthUnit toUnit=ELengthUnit::LU_MET_M, EAutoUnitType AutoUnit=EAutoUnitType::AUT_OFF, bool UseExtendedAutoUnits=false, int precision=1, bool ForceSign=false, bool UseGrouping=false);
	


	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (Keywords = "TicTac"), Category = "TicTacToe UnitFormat")
	static double ConvertWeight(float length, EWeightUnit fromUnit = EWeightUnit::WU_MET_KG, EWeightUnit toUnit = EWeightUnit::WU_MET_KG);

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (Keywords = "TicTac"), Category = "TicTacToe UnitFormat")
	static FText FormatWeight(float weight, EWeightUnit fromUnit=EWeightUnit::WU_MET_KG, EWeightUnit toUnit=EWeightUnit::WU_MET_KG, EAutoUnitType AutoUnit=EAutoUnitType::AUT_OFF, bool UseExtendedAutoUnits=false, int precision=1, bool ForceSign=false, bool UseGrouping=false);



	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (Keywords = "TicTac"), Category = "TicTacToe UnitFormat")
	static double ConvertVolume(float volume, EVolumeUnit fromUnit = EVolumeUnit::VU_MET_CM3, EVolumeUnit toUnit = EVolumeUnit::VU_MET_CM3);

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (Keywords = "TicTac"), Category = "TicTacToe UnitFormat")
	static FText FormatVolume(float volume, EVolumeUnit fromUnit= EVolumeUnit::VU_MET_CM3, EVolumeUnit toUnit= EVolumeUnit::VU_MET_CM3, EAutoVolumeUnitType AutoUnit= EAutoVolumeUnitType::AUT_OFF, bool UseExtendedAutoUnits=false, int precision=1, bool ForceSign=false, bool UseGrouping=false);



	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (Keywords = "TicTac"), Category = "TicTacToe UnitFormat")
	static double ConvertArea(float volume, EAreaUnit fromUnit = EAreaUnit::AU_MET_CM2, EAreaUnit toUnit = EAreaUnit::AU_MET_CM2);

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (Keywords = "TicTac"), Category = "TicTacToe UnitFormat")
	static FText FormatArea(float volume, EAreaUnit fromUnit = EAreaUnit::AU_MET_CM2, EAreaUnit toUnit = EAreaUnit::AU_MET_CM2, EAutoUnitType AutoUnit = EAutoUnitType::AUT_OFF, bool UseExtendedAutoUnits = false, int precision = 1, bool ForceSign = false, bool UseGrouping = false);



	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (Keywords = "Convert"), Category = "TicTacToe UnitFormat")
	static double ConvertTemperature(float temperature, ETemperatureUnit fromUnit = ETemperatureUnit::TU_CEL, ETemperatureUnit toUnit = ETemperatureUnit::TU_CEL);

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (Keywords = "TicTac"), Category = "TicTacToe UnitFormat")
	static FText FormatTemperature(float temperature, ETemperatureUnit fromUnit = ETemperatureUnit::TU_CEL, ETemperatureUnit toUnit = ETemperatureUnit::TU_CEL, int precision = 1, bool ForceSign = false, bool UseGrouping = false);



	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (Keywords = "Convert"), Category = "TicTacToe UnitFormat")
	static double ConvertTime(float time, ETimeUnit fromUnit = ETimeUnit::TU_SEC, ETimeUnit toUnit = ETimeUnit::TU_SEC);

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (Keywords = "TicTac"), Category = "TicTacToe UnitFormat")
	static FText FormatTime(float volume, ETimeUnit fromUnit = ETimeUnit::TU_SEC, ETimeUnit toUnit = ETimeUnit::TU_SEC, bool AutoUnit = false, int precision = 1, bool ForceSign = false, bool UseGrouping = false);



	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (Keywords = "Convert"), Category = "TicTacToe UnitFormat")
	static double ConvertSpeed(float speed, ELengthUnit fromLengthUnit = ELengthUnit::LU_MET_CM, ELengthUnit toLengthUnit = ELengthUnit::LU_MET_CM, ETimeUnit fromTimeUnit = ETimeUnit::TU_SEC, ETimeUnit toTimeUnit = ETimeUnit::TU_SEC);

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (Keywords = "TicTac"), Category = "TicTacToe UnitFormat")
	static FText FormatSpeed(float speed, ELengthUnit fromLengthUnit = ELengthUnit::LU_MET_CM, ELengthUnit toLengthUnit = ELengthUnit::LU_MET_CM, ETimeUnit fromTimeUnit = ETimeUnit::TU_SEC, ETimeUnit toTimeUnit = ETimeUnit::TU_SEC, EAutoUnitType AutoLengthUnit = EAutoUnitType::AUT_OFF, bool UseExtendedAutoUnits = false, int precision = 1, bool ForceSign = false, bool UseGrouping = false);



	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (Keywords = "TicTac"), Category = "TicTacToe UnitFormat")
	static double ConvertPressure(float pressure, EPressureUnit fromUnit = EPressureUnit::PU_MET_PA, EPressureUnit toUnit = EPressureUnit::PU_MET_PA);

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (Keywords = "TicTac"), Category = "TicTacToe UnitFormat")
	static FText FormatPressure(float pressure, EPressureUnit fromUnit = EPressureUnit::PU_MET_PA, EPressureUnit toUnit = EPressureUnit::PU_MET_PA, EAutoPressureUnitType AutoUnit = EAutoPressureUnitType::AUT_OFF, bool UseExtendedAutoUnits = false, int precision = 1, bool ForceSign = false, bool UseGrouping = false);
};
