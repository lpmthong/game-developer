using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows.Forms;
using System.Threading.Tasks;

namespace MapEditor
{
    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            var t = Task.Factory.StartNew(() => Application.EnableVisualStyles());
            var t1 = Task.Factory.StartNew(() => Application.SetCompatibleTextRenderingDefault(false));
            var t2 = Task.Factory.StartNew(() => Application.Run(new frmMain()));
            t2.Wait();
        }
    }
}
