using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Serialization;

namespace EZOrthoDataStructure
{
    [System.Serializable]
    public class IB_DataEntity
    {
        public IB_DataEntity()
        {
            IsDefine = false;
        }
        [XmlAttribute]
        public bool IsDefine;
        public CrownInfo[] Bracket = new CrownInfo[32];
    }
}
