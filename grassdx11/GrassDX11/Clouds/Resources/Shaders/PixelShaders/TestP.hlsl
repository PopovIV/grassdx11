//--------------------------------------------------------------------------------------
// File: Tutorial02.fx
//
// Copyright (c) Microsoft Corporation. All rights reserved.


struct Input
{
    float4 position : SV_POSITION;
};


float4 main(Input input) : SV_TARGET
{
	
    return float4(1.0f, 1.0f, 0.0f, 1.0f); // Yellow, with Alpha = 1
}
