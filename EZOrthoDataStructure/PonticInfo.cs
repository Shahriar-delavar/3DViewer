using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace EZOrthoDataStructure
{
    [System.Serializable]
    public class PonticInfo_CS
    {
        public PonticInfo_CS(){}
        public TriMeshModels model;
        public double[] ModelMatrix = new double[16];
        public Tuple<int,int> TeethPair = new Tuple<int, int>(-1,-1);
    }
}
