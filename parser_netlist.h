#ifndef PARSER_NETLIST_H
#define PARSER_NETLIST_H

#include <fstream>
using namespace std;

const float cap_inv_in  = 0.0109115;
const float cap_nand_a1 = 0.00683597;
const float cap_nand_a2 = 0.00798456;
const float cap_nor_a1  = 0.0105008;
const float cap_nor_a2  = 0.0108106;
const float cap_output  = 0.02;

const int LINE_LENGTH         = 500;
const int FILE_NAME_LENGTH    = 100;
const int MODULE_NAME_LENGTH  = 100;

struct Net;
struct FList;

struct Gate
{
  int    type;
  string name;   // instance name
  Net    *output;   // output net

  enum Type
  {
    UNKNOWN,
    INV,
    NAND,
    NOR
  };
};

struct Net
{
  int    type;
  string name;   // net name
  FList  *fanout;

  enum Type
  {
    INTERNAL,
    INPUT,
    OUTPUT
  };
};

struct FList
{
  Gate   *gate;
  int    port;
  FList  *next;

  enum Port
  {
    NOTHING,
    OUT,
    IN,
    A1,
    A2
  };
};

struct GList
{
   Gate   *data;
   GList  *next;
};

struct NList
{
   Net    *data;
   NList  *next;
};

ifstream  fin;
char      FileAddr[FILE_NAME_LENGTH];
NList     *input_list   = NULL;
NList     *output_list  = NULL;
NList     *net_list     = NULL;
GList     *gate_list    = NULL;

bool OpenFile();
void Parser ();
void Show_Net_info();
void Show_Gate_info();

Net *search_net( NList *list, char *name );
Net *add_net( char *name, Net *data );

#endif

