enum {
  SQ_AF_UNSPEC= 0,
  SQ_AF_UNIX,
  SQ_AF_INET,
  SQ_AF_INET6,
  SQ_AF_APPLETALK,
  SQ_AF_MAX
};

enum {
  SQ_SOCK_UNSPEC= 0,
  SQ_SOCK_STREAM,
  SQ_SOCK_DGRAM,
  SQ_SOCK_RAW,
  SQ_SOCK_RDM,
  SQ_SOCK_SEQPACKET,
  SQ_SOCK_MAX
};

int netInitialise(void);
int netShutdown(void);

int netLookupName(void *name, int nameSize, void *serv, int servSize, int family, int type, int proto, int passive, int semaIndex);
int netLookupCount(int request);
int netLookupResultSize(int request, int index);
int netLookupGetResultInto(int request, int index, void *addressHandle);
int netLookupEnd(int request);

int netAddressSizeStringSizeNumericNodeService(void *sqAddr, int szAddr, int numeric, int node, int serv);
int netAddressSizeGetStringSizeNumericNodeServiceIntoSize(void *sqAddr, int szAddr, int numeric, int node, int serv, void *sqString, int szString);
int netAddressFamily(void *sqAddr, int szAddr);
int netAddressType(void *sqAddr, int szAddr);
int netAddressProtocol(void *sqAddr, int szAddr);


int netLookupBeginNameSizeServiceSizeFamilyPassiveSemaIndex(void *name, int nameSize, void *serv, int servSize, int family, int passive, int semaIndex);
int netLookupResult(int reqIndex);
int netLookupAddressSize(int reqIndex, int index);
int netLookupGetAddressInto(int reqIndex, int index, void *addr, int addrSize);
int netLookupErrorSize(int reqIndex);
int netLookupGetErrorInto(int reqIndex, void *string, int stringSize);

int netAddressFamily(void *addr, int addrSize);

int netProtocolNamed(void *name, int nameSize);

int netInterfaceCount(void);
int netInterfaceSize(int index);
int netInterfaceGetInto(int index, void *sqItf, int sqItfSize);
int netInterfaceNameSize(void *sqItf, int sqItfSize);
int netInterfaceGetNameInto(void *sqItf, int sqItfSize, void *sqName, int sqNameSize);
int netInterfaceAddressSize(void *sqItf, int sqItfSize);
int netInterfaceGetAddressInto(void *sqItf, int sqItfSize, void *sqAddr, int sqAddrSize);

int netSocketCreateFamilyTypeProtocolSemaReadWrite(int handle, int family, int type, int proto, int sema, int readSema, int writeSema);
