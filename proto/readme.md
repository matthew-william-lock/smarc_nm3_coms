# DCCL Interface Descriptor Language (IDL)

DCCL uses the Google Protocol Buffers (Protobuf) language to define messages. More details can be founnd at the [DCCL v4 docs](https://libdccl.org/4.0/idl.html).

# Google Protocol Buffers (Protobuf)

## General Tips for Protobufs

## Assigning Field Numbers

Each field in the message definition has a unique number. These field numbers are used to identify your fields in the message binary format, and should not be changed once your message type is in use. Note that field numbers in the range 1 through 15 take one byte to encode, including the field number and the field’s type (you can find out more about this in Protocol Buffer Encoding). Field numbers in the range 16 through 2047 take two bytes. So you should reserve the numbers 1 through 15 for very frequently occurring message elements. Remember to leave some room for frequently occurring elements that might be added in the future.