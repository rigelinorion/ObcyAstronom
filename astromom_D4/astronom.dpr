program astronom;

uses
  Forms,
  main_form in 'main_form.pas' {Form1},
  Unit2 in 'Unit2.pas' {Form2},
  Scanf in 'Scanf.pas';

{$R *.RES}

begin
  Application.Initialize;
  Application.CreateForm(TForm1, Form1);
  Application.CreateForm(TForm2, Form2);
  Application.Run;
end.
