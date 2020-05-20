using System;
using System.IO;
using System.Linq;

namespace EZOrthoDataStructure
{
    [System.Serializable]
    public class IW_ModelStructure
    {
        public IW_Point3d[] vertex;
        public IW_triIdx[] face;
        public IW_Point3d[] color;

        string Convert(byte[] data)
        {
            char[] characters = data.Select(b => (char)b).ToArray();
            return new string(characters);
        }

        public byte[] BinarySerialization()
        {
            byte[] tmpArray;
            MemoryStream stream = new MemoryStream();
            using (BinaryWriter writer = new BinaryWriter(stream))
            {
                int verNum = vertex.Length;
                int faceNum = face.Length;

                writer.Write(verNum);
                writer.Write(faceNum);

                for (int i = 0; i < verNum; i++)
                {
                    writer.Write((float)vertex[i].x);
                    writer.Write((float)vertex[i].y);
                    writer.Write((float)vertex[i].z);
                }
                for (int i = 0; i < faceNum; i++)
                {
                    writer.Write(face[i].a);
                    writer.Write(face[i].b);
                    writer.Write(face[i].c);
                }

                //(Optional)
                try
                {
                    if (color != null)
                    {
                        int colorNum = color.Length;
                        writer.Write(colorNum);
                        for (int i = 0; i < colorNum; i++)
                        {
                            writer.Write((float)color[i].x);
                            writer.Write((float)color[i].y);
                            writer.Write((float)color[i].z);
                        }
                    }
                }
                catch (System.Exception ex)
                {
                	
                }
               
                stream.Flush();
                tmpArray = stream.ToArray();
            }
            return tmpArray;
        }

        public void BinaryDeserialization(byte[] DataArray)
        {
            if (DataArray == null)
                throw new SystemException("No data");

            MemoryStream stream = new MemoryStream(DataArray);
            using (BinaryReader reader = new BinaryReader(stream))
            {
                try
                {
                    int verNum = reader.ReadInt32();
                    int faceNum = reader.ReadInt32();

                    vertex = new IW_Point3d[verNum];
                    face = new IW_triIdx[faceNum];
                    for (int i = 0; i < verNum; i++)
                    {
                        vertex[i] = new IW_Point3d();
                        vertex[i].x = (double)reader.ReadSingle();
                        vertex[i].y = (double)reader.ReadSingle();
                        vertex[i].z = (double)reader.ReadSingle();
                    }
                    for (int i = 0; i < faceNum; i++)
                    {
                        face[i] = new IW_triIdx();
                        face[i].a = reader.ReadInt32();
                        face[i].b = reader.ReadInt32();
                        face[i].c = reader.ReadInt32();
                    }


                    //(Optional)
                    try
                    {
                        bool has_color = (reader.BaseStream.Position < reader.BaseStream.Length);/*reader.PeekChar() != -1  .net在讀 UTF-8 有問題 */
                        if (has_color)
                        {
                            int colorNum = reader.ReadInt32();
                            color = new IW_Point3d[colorNum];
                            for (int i = 0; i < colorNum; i++)
                            {
                                color[i] = new IW_Point3d();
                                color[i].x = (double)reader.ReadSingle();
                                color[i].y = (double)reader.ReadSingle();
                                color[i].z = (double)reader.ReadSingle();
                            }
                        }
                    }
                    catch (System.Exception ex)
                    {
                        string msg = ex.Message;
                        color = null;
                    }
                  

                }
                catch (System.Exception ex)
                {
                    vertex = new IW_Point3d[0];
                    face = new IW_triIdx[0];
                    color = null;
                }
            }
        }
    }
}
