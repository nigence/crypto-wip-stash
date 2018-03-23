using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using System.Runtime.InteropServices;

namespace SHA3utilityUserCs
{
    public class SHA3utilityInterface
    {
        [DllImport("SHA3utility.dll", EntryPoint = "getFileSha3", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool getFileSha3(string filename, StringBuilder digest, int maxDigestLength);
    }
}
