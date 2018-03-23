using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

namespace SHA3utilityUserCs
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("SHA3utility test from c#");

            string filename = "C:\\Xray\\Data\\TestSet\\Sample002.jpg";
            StringBuilder digest = new StringBuilder( 48*2+1 );
            bool okay =  SHA3utilityInterface.getFileSha3(filename, digest, 48*2+1 );
            
            if (!okay)
		        Console.WriteLine("ERROR! Problems getting hash..." );
	        else
            {
		        Console.WriteLine("Sample002.jpg SHA3 hash is ...\n");
		        Console.WriteLine(digest);
            }
            
            Console.WriteLine("Press any key to exit.");
            Console.ReadKey();
        }
    }
}
