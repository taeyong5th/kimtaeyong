#pragma once

/*
128px = 1m
*/
int PixelToMeter(int x)
{	
	return (x >> 7);
}