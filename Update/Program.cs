using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Update
{
    class Program
    {
        public struct CrossData
        {
            public string OldHash { set; get; }
            public string NewHash { set; get; }
            public string Offset { set; get; }
            public string Name { set; get; }
            public string version { set; get; }

        }
        static void Main(string[] args)
        {
            int couter = 0;
            Dictionary<string, CrossData> data = new Dictionary<string, CrossData>();
            Dictionary<string, string> MikeDiction = new Dictionary<string, string>();//Origin new
            Dictionary<string, string> AllDiction = new Dictionary<string, string>();//Origin new
            using (StreamReader reader = new StreamReader("HashMapData.h"))
            {
                while (!reader.EndOfStream)
                {
                    string str = reader.ReadLine();
                    str = str.Replace("X(", "");
                    str = str.Replace(" ", "");
                    str = str.Replace(")", "").ToLower();
                    string[] split = str.Split(',');
                    //X(OldHash, NewHash, Offset, Name, Version)
                    if (split[0].StartsWith("0x") && split.Count() == 5)
                    {
                        CrossData mydata = new CrossData();
                        mydata.OldHash = split[0];
                        mydata.NewHash = split[1];
                        mydata.Offset = split[2];
                        mydata.Name = split[3];
                        mydata.version = split[4];
                        if (!data.ContainsKey(mydata.OldHash))
                            data.Add(mydata.OldHash, mydata);
                        else
                        {
                            data[mydata.OldHash] = mydata;
                        }
                    }

                }

            }
            using (StreamReader reader = new StreamReader("crossMap.txt"))
            {
                while (!reader.EndOfStream)
                {
                    string str = reader.ReadLine();
                    string[] split = str.Split(',');
                    if (!AllDiction.ContainsKey(split[0]))
                        AllDiction.Add(split[0], split[1]);
                    else
                        AllDiction[split[0]] = split[1];
                }
            }
            using (StreamReader reader = new StreamReader("Mike'sCrossMap.txt"))
            {
                while (!reader.EndOfStream)
                {
                    string str = reader.ReadLine();
                    string[] split = str.Split(',');
                    if (!MikeDiction.ContainsKey(split[0]))
                        MikeDiction.Add(split[0], split[1]);
                    else
                        MikeDiction[split[0]] = split[1];
                }
            }
            List<string> Updated = new List<string>();
            List<string> NeedtoUpdate = new List<string>();

            foreach (KeyValuePair<string, CrossData> item in data)
            {
                if (MikeDiction.ContainsKey(item.Key))
                {
                    Updated.Add($"X({item.Key}," +
                            $"{MikeDiction[item.Key]}," +
                            $"{item.Value.Offset}," +
                            $"{item.Value.Name}," +
                            $"{item.Value.version})//Mike");
                }
                else if (AllDiction.ContainsKey(item.Key))
                {
                    Updated.Add($"X({item.Key}," +
                           $"{AllDiction[item.Key]}," +
                           $"{item.Value.Offset}," +
                           $"{item.Value.Name}," +
                           $"{item.Value.version})//Others");
                }
                else if (item.Value.OldHash == item.Value.NewHash)//基础函数
                {
                    Updated.Add($"X({item.Key}," +
                           $"{item.Key}," +
                           $"{item.Value.Offset}," +
                           $"{item.Value.Name}," +
                           $"{item.Value.version})//Never Change");
                }
                else
                {
                    couter++;
                    NeedtoUpdate.Add($"//X({item.Key}," +
                          $"{item.Value.NewHash}," +
                          $"{item.Value.Offset}," +
                          $"{item.Value.Name}," +
                          $"{item.Value.version})//Need to update");
                }
            }
            using (StreamWriter writer = new StreamWriter("newHash.h", true))
            {
                foreach (string str in Updated)
                {
                    writer.WriteLine(str);
                }
                foreach (string str2 in NeedtoUpdate)
                {
                    writer.WriteLine(str2);
                }
            }
            Console.WriteLine("DOne {0}", couter);
            Console.ReadKey();
        }
    }
}
