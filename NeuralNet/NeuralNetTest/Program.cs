using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using NeuralNetWrapper;

namespace NeuralNetTest
{
    class Program
    {
        static void Main(string[] args)
        {
            NeuralNet net = new NeuralNet(new int[] { 2, 2, 1 });
            for(int i = 0; i < 10000; i++)
            {
                net.Learn(new double[] { 0.0, 0.0 }, new double[] { 0.0 });
                net.Learn(new double[] { 0.0, 1.0 }, new double[] { 1.0 });
                net.Learn(new double[] { 1.0, 0.0 }, new double[] { 1.0 });
                net.Learn(new double[] { 1.0, 1.0 }, new double[] { 0.0 });
            }
            double[] result = new double[] { 0.0 };

            net.Run(new double[] { 0.0, 0.0 }, result);
            Console.WriteLine("0.0, 0.0 => " + result[0]);

            net.Run(new double[] { 0.0, 1.0 }, result);
            Console.WriteLine("0.0, 1.0 => " + result[0]);

            net.Run(new double[] { 1.0, 0.0 }, result);
            Console.WriteLine("1.0, 0.0 => " + result[0]);

            net.Run(new double[] { 1.0, 1.0 }, result);
            Console.WriteLine("1.0, 1.0 => " + result[0]);

            Console.WriteLine("test completed. Press Enter key to finish.");
            Console.ReadLine();
        }
    }
}
