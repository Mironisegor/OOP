using System;
using System.Drawing.Drawing2D;
using System.Windows.Forms;

public class ProgressionForm : Form
{
    private Label labelStart;
    private Label labelEnd;
    private Label labelStep;
    private Label labelType;
    private TextBox textBoxStart;
    private TextBox textBoxEnd;
    private TextBox textBoxStep;
    private ComboBox comboBoxType;
    private Button buttonCalculate;
    private Label labelResult;

    public ProgressionForm()
    {
        this.Text = "Прогрессии"; //Название окна
        this.Size = new System.Drawing.Size(400, 250); //Размер окна

        labelStart = new Label() { Left = 30, Top = 20, Text = "Начало:" };
        textBoxStart = new TextBox() { Left = 130, Top = 20, Width = 150 };

        labelEnd = new Label() { Left = 30, Top = 50, Text = "Конец:" };
        textBoxEnd = new TextBox() { Left = 130, Top = 50, Width = 150 };

        labelStep = new Label() { Left = 30, Top = 80, Text = "Шаг:" };
        textBoxStep = new TextBox() { Left = 130, Top = 80, Width = 150 };

        labelType = new Label() { Left = 30, Top = 110, Text = "Тип прогрессии:" };
        comboBoxType = new ComboBox() { Left = 130, Top = 110, Width = 150 };
        comboBoxType.Items.AddRange(new object[] { "Линейная", "Геометрическая" });
        comboBoxType.SelectedIndex = 0;

        buttonCalculate = new Button() { Text = "Вычислить", Left = 100, Top = 140, Width = 150 };
        buttonCalculate.Click += new EventHandler(ButtonWork);
        buttonCalculate.BackColor = Color.Blue;
        buttonCalculate.ForeColor = Color.White;

        labelResult = new Label() { Left = 130, Top = 170, Width = 250, Height = 50 };

        this.Controls.Add(labelStart);
        this.Controls.Add(textBoxStart);
        this.Controls.Add(labelEnd);
        this.Controls.Add(textBoxEnd);
        this.Controls.Add(labelStep);
        this.Controls.Add(textBoxStep);
        this.Controls.Add(labelType);
        this.Controls.Add(comboBoxType);
        this.Controls.Add(buttonCalculate);
        this.Controls.Add(labelResult);
    }

    private void ButtonWork(object sender, EventArgs e)
    {
        labelResult.Text = String.Empty;
        // Проверка на пустые поля
        if (string.IsNullOrWhiteSpace(textBoxStart.Text) ||
            string.IsNullOrWhiteSpace(textBoxEnd.Text) ||
            string.IsNullOrWhiteSpace(textBoxStep.Text))
        {
            MessageBox.Show("Заполните все поля");
            return;
        }

        double start, end, step, sum;
        //Проверка на возможность преобразовать в double
        try
        {
            start = Convert.ToDouble(textBoxStart.Text);
            end = Convert.ToDouble(textBoxEnd.Text);
            step = Convert.ToDouble(textBoxStep.Text);
        }
        catch
        {
            MessageBox.Show("Невозможно выполнить преобразование типов");
            return;
        }

        Progression progression;
        if (comboBoxType.SelectedIndex == 0)
        {
            progression = new Linear();
        }
        else
        {
            progression = new Exponential();
        }

        sum = progression.CalculateSum(start, end, step);
        labelResult.Text = $"Сумма прогрессии: {sum}";
        labelResult.ForeColor = Color.Green;
    }

    [STAThread]
    public static void Main()
    {
        Application.Run(new ProgressionForm());
    }
}
