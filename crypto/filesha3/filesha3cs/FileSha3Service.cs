using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace filesha3cs
{
    static class FileSha3Service
    {
        public static void CalcSha3( string filePathname, ref string outputDigest, ref bool okay )
        {
            outputDigest = "DEADBEEF";
            okay = true;
        }
    }
}
