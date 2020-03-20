**Client -> Server**

Messages:

* Connectionless:
	* Connect
		- string - client's IP to check whether he can connect at all (ban/white/black-lists)
		- string - client's preffered nickname

* Connection:
	* Disconnect
	* Command
		- string

**Server -> Client**

Events:

* Spawn:
	- vec3 (floats/doubles) - pos
	- quat - rot?

* Item added
	- string - loc string for name?
	- (u)int32 - amount

* Item removed (can also be just an item pickup with negative amount)
	- string - loc string for name?
	- (u)int32 - amount

* Experience gained
	- (u)int32 - amount

* Location discovered
	- string - location name

* Level up
	- (u)int32 - level

Messages:

* Inventory data
	- for each item
		- string - loc string for name?
		- string/uint32 - type?
		- string - image?
		- (u)int32 - amount

* Player state
	- (u)int32 - health
	- float/(u)int32 - hunger
	- (u)int32 - rads