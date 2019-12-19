**Client -> Server**

Messages:
	Connectionless:
		* Connect
			- string - client's IP to check whether he can connect at all (ban/white/black-lists)
			- string - client's preffered nickname
	Connection:
		* Command
			- string

**Server -> Client**

Events:
* Spawn:
	- vec3 (floats/doubles) - pos
	- quat - rot?

* Item pickup
	- string - loc string for name?

Messages:
* Inventory data
	- for each item
		- string - loc string for name?
		- string/uint32 - type?
		- string - image?
		- (u)int32 - amount