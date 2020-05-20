using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace EZOrthoDataStructure
{
    [System.Serializable]
    public class ProjectInstructionWP
    {
        public ProjectInstructionWP(){ }
        public int[] ToothState = new int[32];
        public bool[] AttachmentEnalbe = new bool[32];
        public bool[] IPREnable = new bool[32];//15沒用到 31也沒用到
        public string MaxillaFilePath = "";
        public string MandibleFilePath = "";
    }
}
