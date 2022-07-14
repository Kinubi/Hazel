using System;

namespace Hazel
{
    public class Main
    {
        public float FloatVar { get; set; }

        public Main()
        {
            Console.WriteLine("Main constructor!");
        }

        public void PrintMessage()
        {
            Console.WriteLine("Hello world from C#!");
        }

        public void PrintCustomMessage(string message)
        {
            Console.WriteLine($"C# says: {message}");
        }

        public void PrintCustomMessageInt(int value)
        {
            Console.WriteLine($"C# says: {value}");
        }
    }
}