'From Squeak3.7 of ''4 September 2004'' [latest update: #5989] on 19 October 2004 at 3:42:24 pm'!

My instance variables:

lastHash - the lastHash that was assigned...I use the same algorithm to generate hashes as the VM
hashMap - A dictionary of all assigned identity hashes 

Subclasses can extend me if they need to write new images with modified hash values.!
	"Do nothing.  Here so sending this to a Set does not have to do a time consuming respondsTo:"

	^self rehash! !

	| object newDict |
	newDict := self shallowCopy.
	newDict withArray: (Array new: array size).
	1 to: array size do:
		[ :i |
		object := array at: i.
		object ifNotNil:
			[newDict
				noCheckAdd: object
				hash: (tracer newHashFor: object key)]].
	^newDict! !
	"Variant to allow the hash to be specified
	by the caller.  8/23/02 svp"

	array at: (self findElementOrNil: anObject key hash: hash) put: anObject.
	tally _ tally + 1! !

	| newDict key |
	newDict := self class basicNew: self basicSize.
	newDict init: array size.
	1 to: self basicSize do: 
		[ :i |
		key := self basicAt: i.
		key ifNotNil: 
			[newDict 
				noCheckAt: key 
				put: (array at: i) 
				hash: (tracer newHashFor: key)]].
	^newDict! !
	"Set the value at key to be value."
	| index |
	index _ self findElementOrNil: key hash: identityHash.
	(self basicAt: index) == nil
		ifTrue: 
			[tally _ tally + 1.
			self basicAt: index put: key].
	array at: index put: value.
	^ value! !
	"My hash is independent of my oop."

	"While this statement is technically correct, it is misleading.  My hash does
	depend on the identity hash of my species, therefore it does need special care
	when cloning an image with new identity hashes - svp"

	^String stringHash: self initialHash: (self species hashMappedBy: map)! !
	"** DELETEME ** Overridden here to work with DVS packaging mechanism."

	^super hashMappedBy: map! !
	"Note, we cannot use allObjectsDo: because some objects like to swap identities
	during a rehash...this means that allObjectsDo: will not find all objects.  Also, this
	algorithm delays become operations to the very end where we can do them all at once. -svp"
	| objectCount allObjects numMdicts oldObjs newObjs newObject |

	numMdicts := MethodDictionary allInstances size.
	oldObjs := OrderedCollection new: numMdicts.
	newObjs := OrderedCollection new: numMdicts.

	"Create an array big enough to hold all objects in memory"
	objectCount := 0.
	self systemNavigation allObjectsDo: [ :ea | objectCount := objectCount + 1].
	allObjects := Array new: objectCount + 500.

	"Now fill the array"
	objectCount := 0.
	self systemNavigation allObjectsDo: [ :ea | allObjects at: (objectCount := objectCount + 1) put: ea ].

"Progress bar disabled until proven innocent here..."
		displayProgressAt: Display center
		from: 1 to: objectCount
		during: [:bar | "
			objectCount := 0.
			allObjects do: [ :ea |
				"bar value:" (objectCount := objectCount + 1).
				newObject := ea rehashWithoutBecome.
				(newObject ~~ ea) ifTrue: 
					[oldObjs add: ea.
					newObjs add: newObject].
			].
			oldObjs asArray elementsExchangeIdentityWith: newObjs asArray.
		"]."! !
	"Subclasses may want to add converted objects to swap map before starting trace but after shuting down extra processes"

	| sets elementCount clone |
	hashMap := LargeIdentityDict new: elementCount.
		clone := ea cloneUsingHashesFrom: self.
		swapMap at: ea put: clone].
	"Answer a new pseudo-random number for use as an identity hash."

	lastHash := 13849 + (27181 * lastHash) bitAnd: 65535.
	^ lastHash bitAnd: self hashMask
! !
	"The sets listed here get rehashed using the newly assigned identity hash values before the clone is written.  On startup, the clone image will rehash all objects to ensure that all hashed structures are properly arranged.  Rehashing is done in this two step process to retain maximum flexibility (if we tried to do everything up front, we would need to update the tracer every time a new type of Set is added with a different hashing and scanning algorithm, plus it would make the hashMap very large and slow)."

! !

	Smalltalk rehashEntireImage! !

	^ hashMap at: object ifAbsent: [self newObjectHash]
! !

	^lastHash! !

	| aligned |

	| newSet object |
	newSet := self class basicNew init: array size.
	1 to: array size do:
		[ :i |
		object := array at: i.
		(object == flag or: [object == nil]) ifFalse:
			[newSet 
				noCheckAdd: object
				hash: (object hashMappedBy: tracer)]].
	^newSet! !
	array at: (self findElementOrNil: anObject hash: hash) put: anObject.
	tally _ tally + 1! !