# SSVLongTime

Library (Singleton Class) to get UpTime of your Arduino- or ESP- compatible device.
Function getUpTimeSec() returns up-time in seconds as uint32_t type, does not overfloat as fast as millis().
Also has function millis64() which returns up-time im milliseconds (as millis()), but as uint64_t type, so also isn't overfloat so fast. 
But keep in mind 64-git operations may be significantly slower.
