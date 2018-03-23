using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace filesha3cs
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Crypto file SHA3 servise tester");

            string filePathname = "Dummy\\path\\name\\tofile.ext";
            string outputDigest = "";
            bool okay = false;

            FileSha3Service.CalcSha3(filePathname, ref outputDigest, ref okay);

            if (okay)
            {
                Console.WriteLine("Hash is ...");
                Console.WriteLine(outputDigest);
            }
            else
                Console.WriteLine("ERROR! There were problems hashing the file.");

            // Keep the console window open in debug mode.
            Console.WriteLine("Press any key to exit.");
            Console.ReadKey();
        }
    }
}
