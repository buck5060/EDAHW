#include <string.h>
#include <iostream>
#include "parser_netlist.h"
using namespace std;

int main( int argc, char** argv )
{
	if ( OpenFile() )
  {
		Parser();
		Show_Net_info();
		Show_Gate_info();
    fin.close();
	}

  //system( "pause" );
  return 0;
}

bool OpenFile()
{
	cout << "input File Address : ";
	cin  >> FileAddr;
	fin.open( FileAddr );

  return ( !fin ) ? false : true ;
}

void Parser ()
{
  char    *token;
  char    line[LINE_LENGTH];
  char    module_name[MODULE_NAME_LENGTH];
  NList   *nlist_end;
  NList   *nltemp;
  GList   *glist_end;
  GList   *gltemp;
  FList   *fltemp;
  Net     *ntmp;
  Gate    *gtmp;

  while ( fin.getline( line , LINE_LENGTH ) ) // search module name
  {   
    if ( token = strtok( line , " " ) )
    {
      if ( strcmp( token , "module" ) == 0 )
      {
        token = strtok( NULL , "(" );
        strcpy( module_name , token );
        break;
      }
    }
    else strcpy( module_name , "not found" );
  }
  cout << "module " << module_name << " found!!\n";

// first part: input and output ports list
  int   io_parse  = 0;
  int   type      = Net::INTERNAL;
  bool  end_mark;
  bool  empty     = true;
  
  nlist_end       = NULL;
  
  // search input/output
  while ( io_parse < 2 && fin.getline( line , LINE_LENGTH ) )
  {   
    end_mark = false;
    
    for ( int i = 0 ; line[i] != '\0'; i++ ) // separate token
    {   
       switch( line[i] )
       {
         case ';':  end_mark  = true;         // finish marker appears
         case ',':  line[i]   = ' ';    break;
         case ' ':                      break;
         default:   empty     = false;  break;
       }
    }
    if ( empty ) continue;   // empty line skipped

    if ( type == Net::INTERNAL ) // reset, find input/output keyword
    { 
      if ( token = strtok( line , " " ) )
      {
        if      ( strcmp( token , "input"  ) == 0     ) type = Net::INPUT;
        else if ( strcmp( token , "output" ) == 0     ) type = Net::OUTPUT;
        else if ( token[0] == '/' && token[1] == '/'  ) continue; // comment
        
        token = strtok( NULL , " " );   // get next token
      }
      else continue;   // no token
    }
    else token = strtok( line , " " );   // get first token

    if ( token[0] == '/' && token[1] == '/' ) continue; // comment

    if ( type == Net::INPUT )
    {
      cout << "Get input list\n";
      
      while ( token ) // input name
      {   
        // add into input list
        ntmp          = new( Net );
        ntmp->type    = Net::INPUT;   // input
        ntmp->name    = token;
        ntmp->fanout  = NULL;

        nltemp        = new( NList );
        nltemp->data  = ntmp;
        nltemp->next  = NULL;

        if      ( !input_list ) input_list  = nlist_end       = nltemp;
        else if ( nlist_end   ) nlist_end   = nlist_end->next = nltemp;
        else                    cout << "Input list error !!" << endl;
        
        // add into net list
        add_net( token , ntmp );
        token = strtok( NULL , " " );   // next token
      }

      if ( end_mark ) // end mark is found, finish input list
      {   
        io_parse++;
        type      = Net::INTERNAL;
        nlist_end = NULL;
      }
      else cout << "line continued!!\n";
    }
    else if ( type == Net::OUTPUT )
    {
      cout << "Get output list\n";
      
      while ( token ) // output name
      {   
        // add into output list
        ntmp          = new( Net );
        ntmp->type    = Net::OUTPUT;   // output
        ntmp->name    = token;
        ntmp->fanout  = NULL;

        nltemp        = new( NList );
        nltemp->data  = ntmp;
        nltemp->next  = NULL;

        if      ( !output_list  ) output_list = nlist_end       = nltemp;
        else if ( nlist_end     ) nlist_end   = nlist_end->next = nltemp;
        else                      cout << "Output list error !!" << endl;

        // add into net list
        add_net( token , ntmp );
        token = strtok( NULL , " " );   // next token
      }

      if ( end_mark ) // end mark is found, finish input list
      {   
        io_parse++;
        type      = Net::INTERNAL;
        nlist_end = NULL;
      }
      else cout << "line continued!!\n";
    }
  }

// second part: gate netlist
  glist_end = gate_list;
  while ( glist_end && glist_end->next ) glist_end = glist_end->next;

  nlist_end = net_list;
  while ( nlist_end && nlist_end->next ) nlist_end = nlist_end->next;

  int port_case = FList::NOTHING;

  while ( fin.getline( line , LINE_LENGTH ) ) // search gates
  {   
    end_mark  = false;
    empty     = true;

    for ( int i = 0 ; line[i] != '\0' ; i++ ) // separate token
    {   
       switch( line[i] )
       {
         case ';':  end_mark  = true;         // finish marker appears
         case ',':
         case '(':
         case ')':  line[i]   = ' ';    break;
         case ' ':                      break;
         default:   empty     = false;  break;
       }
    }

    if ( empty ) continue;   // empty line skipped

    // get first keyword
    if ( token = strtok( line , " " ) )
    {
      if      ( strcmp( token , "INVX1"     ) == 0 )  type = Gate::INV;
      else if ( strcmp( token , "NANDX1"    ) == 0 )  type = Gate::NAND;
      else if ( strcmp( token , "NOR2X1"    ) == 0 )  type = Gate::NOR;
      else if ( strcmp( token , "endmodule" ) == 0 )  break;
      else if ( token[0] == '/' && token[1] == '/' )  continue;   // comment
      else                                            type = Gate::UNKNOWN;   // unknown gate type

      if ( type > Gate::UNKNOWN ) // find a gate
      {   
        cout << "Gate "     << token << " found!!";
        token = strtok( NULL , " " );   // get instance name
        cout << " (name: "  << token << ")\n";

        gtmp          = new( Gate );   // add this gate into pool
        gtmp->type    = type;
        gtmp->name    = token;
        gtmp->output  = NULL;

        gltemp        = new( GList );
        gltemp->data  = gtmp;
        gltemp->next  = NULL;

        if      ( !gate_list  ) gate_list = glist_end       = gltemp;
        else if ( glist_end   ) glist_end = glist_end->next = gltemp;
        else                    cout << "Gate list error !!" << endl;

        // scan port name
        while ( token = strtok( NULL , " " ) ) // port connection
        {   

          if      ( strcmp( token , ".ZN" ) == 0 ) port_case = FList::OUT; // output net
          else if ( strcmp( token ,  ".I" ) == 0 ) port_case = FList::IN;  // input net
          else if ( strcmp( token , ".A1" ) == 0 ) port_case = FList::A1;
          else if ( strcmp( token , ".A2" ) == 0 ) port_case = FList::A2;
          else
          {
            port_case = FList::NOTHING;
            cout << "Unknown token in gate " << gtmp->name << " !!\n";
          }

          if ( token = strtok( NULL , " " ) ) // net name
          {   
            ntmp = search_net( net_list , token );

            if ( !ntmp )
            {
              ntmp = add_net( token , NULL);
              if ( !ntmp )  cout << "Add Net " << token << " Error!!\n";
            }
            else            cout << "Net " << ntmp->name << " exist!!\n";
          }
          else ntmp = NULL;

          if ( ntmp )
          {
            if      ( port_case ==  FList::OUT ) gtmp->output = ntmp;
            else if ( port_case >   FList::OUT ) // add fanout gate
            {   
              fltemp        = new( FList );
              fltemp->gate  = gtmp;
              fltemp->port  = port_case;
              fltemp->next  = NULL;

              if ( ntmp->fanout ) fltemp->next = ntmp->fanout;
              ntmp->fanout = fltemp;
            }
          }
        }  // end port scan

        if ( !end_mark ) cout << "Gate declaration is not finished !!\n";
      }
      else cout << "Unknown gate type " << token << " skipped!!\n";
    }
  }  // end gate scan
  cout << "Finish parsing netlist!!\n";
}

void Show_Net_info()
{
  ofstream  fptr;
  char      *token;
  char      filename[FILE_NAME_LENGTH];

  token = strtok( FileAddr , "." );
  strcpy( filename , token   );
  strcat( filename , ".nett"  );
  fptr.open( filename );
  NList *cur;
  FList *fan;

  fptr << "Input net:\n";
  for ( cur = input_list ; cur != NULL ; cur = cur->next )
     fptr << cur->data->name << endl;

  fptr << "\nOutput net:\n";
  for ( cur = output_list ; cur != NULL ; cur = cur->next )
     fptr << cur->data->name << endl;

   // show net list and its fanout gate
  fptr << "\nNet list:\n";
  for ( cur = net_list ; cur != NULL ; cur = cur->next )
  {
     fptr << cur->data->name;

     switch( cur->data->type )
     {
       case Net::INPUT:   fptr << " (PI)\n";                              break;
       case Net::OUTPUT:  fptr << "\n --> primary output";
                          fptr << ", loading = " << cap_output << "pF\n"; break;
       default:           fptr << endl;                                   break;
     }

     for ( fan = cur->data->fanout ; fan != NULL ; fan = fan->next )
     {
        fptr << " --> " << fan->gate->name << "(port: ";

        switch( fan->port )
        {
          case FList::IN:

            fptr << "I)";
            fptr << ", loading = " << cap_inv_in << "pF";
            break;

          case FList::A1:

            fptr << "A1)";
            fptr << ", loading = ";
            
            switch( fan->gate->type )
            {
              case Gate::NAND:  fptr << cap_nand_a1 << "pF"; break;
              case Gate::NOR:   fptr << cap_nor_a1  << "pF"; break;
            }
            break;

          case FList::A2:

            fptr << "A2)";
            fptr << ", loading = ";
            
            switch( fan->gate->type )
            {
              case Gate::NAND:  fptr << cap_nand_a2 << "pF"; break;
              case Gate::NOR:   fptr << cap_nor_a2  << "pF"; break;
            }
            break;

          default: fptr << " )";
        }
        fptr << endl;
     }
  } // end net list

  fptr.close();
} // Show_Net_info

void Show_Gate_info()
{
  ofstream  fptr;
  char      *token;
  char      filename[FILE_NAME_LENGTH];

  token = strtok( FileAddr , "." );
  strcpy( filename , token  );
  strcat( filename , ".gatt" );
  fptr.open( filename );

  GList *cur;

  // show gate list and its fanout net
  for ( cur = gate_list ; cur != NULL ; cur = cur->next )
  {
     fptr << cur->data->name << " (";

     switch( cur->data->type )
     {
       case Gate::INV:  fptr << "INV";  break;
       case Gate::NAND: fptr << "NAND"; break;
       case Gate::NOR:  fptr << "NOR";  break;
       default:         fptr << " ";    break;
     }

     fptr << "), output = " << cur->data->output->name << endl;
  } // end gate list

  fptr.close();
} // Show_Gate_info

Net *search_net( NList *list, char *name )
{
   NList *cur;

   for ( cur = list ; cur != NULL ; cur = cur->next )
      if ( cur->data && strcmp( cur->data->name.c_str() , name ) == 0 )
        return cur->data;
   return NULL;
}

Net *add_net( char *name, Net *data )
{
  Net    *ntmp;
  NList  *nltemp;
  NList  *pre = NULL;
  NList  *cur = net_list;
  int    cmp;

  if ( !data )
  {
        ntmp          = new( Net );
        ntmp->type    = Net::INTERNAL;
        ntmp->name    = name;
        ntmp->fanout  = NULL;
  }
  else  ntmp          = data;

  nltemp       = new( NList );
  nltemp->data = ntmp;
  nltemp->next = NULL;

  if ( !net_list ) // empty list
  {   
    net_list = nltemp;
    return ntmp;
  }

  while ( cur != NULL )
  {
    if ( cur->data )
    {
      cmp = strcmp( cur->data->name.c_str() , name );
      
      if      ( cmp ==  0 ) // net exist
      {   
        delete nltemp;
        if ( !data ) delete ntmp;

        return cur->data;
      }
      else if ( cmp >   0 ) // insert here
      {   
        nltemp->next = cur;
        
        if ( !pre ) net_list  = nltemp;   // single item
        else        pre->next = nltemp;

        return ntmp;
      }
    }
    pre = cur;
    cur = cur->next;
  }

  // insert to the tail
  if (!pre)  net_list  = nltemp;   // single item
  else       pre->next = nltemp;

  return ntmp;
}
