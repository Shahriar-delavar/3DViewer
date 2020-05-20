using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace EZOrthoDataStructure
{
    [System.Serializable]
    public class TriMeshModels
    {
        public byte[] UpperScanModel;
        public byte[] LowerScanModel;

        public byte[][] tooth = new byte[32][];
        public byte[] uppergum;
        public byte[] lowergum;
    }
}
