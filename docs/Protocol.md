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

* Connectionless:
	* Connection accept
	* Connection deny
	or
	* Connection response (accept/deny)
		- 1 bit - accept/deny
		- string/(u)int8 - denial reason (optional)
	* Cell cache data
		- foreach(cell in cells)
			if(server cell != client cell) // formID + md5?
				send data about the cell to the client

* Connection:
	* Inventory data
		- for each item
			- string - loc string for name?
			- string/uint32 - type?
			- string - image?
			- (u)int32 - amount

	* Player state
		- float/(u)int32 - health
		- float/(u)int32 - hunger
		- float/(u)int32 - rads
		- float/(u)int32 - sleep

	* Load cell
		- (u)int32 - id

	* Unload cell
		- (u)int32 - id