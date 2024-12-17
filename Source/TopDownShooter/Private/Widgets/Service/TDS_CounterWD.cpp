#include "TDS_CounterWD.h"
#include "Components/TextBlock.h"



void UTDS_CounterWD::SetCurrentNum(const int32 InNum)
{
	CurrentNum = InNum;
	OutputFinalCount();
}

void UTDS_CounterWD::SetMaxNum(const int32 InNum)
{
	MaxNum = InNum;
	OutputFinalCount();
}

void UTDS_CounterWD::OutputFinalCount()
{
	if (!CurrentNumText) return;

	FString Output = FString::FromInt(CurrentNum);
	Output.Append("/");
	if (MaxNum < 0)
	{
		Output.Append("---");
	}
	else
	{
		Output.Append(FString::FromInt(MaxNum));
	}

	CurrentNumText->SetText(FText::FromString(Output));
}
