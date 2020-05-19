unit main_form;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, ComCtrls, ToolWin, NMUDP, Spin, ExtCtrls, Buttons, scanf,
  OleCtrls, NMHTML, Psock, NMHttp, NMSTRM, VrControls, VrWheel, VrBlinkLed,
  VrCompass;

type
  TForm1 = class(TForm)
    PageControl1: TPageControl;
    TabSheet2: TTabSheet;
    TabSheet4: TTabSheet;
    udp: TNMUDP;
    TabSheet1: TTabSheet;
    check_cameraenabled: TCheckBox;
    radio_preview_on: TRadioGroup;
    GroupBox1: TGroupBox;
    Panel1: TPanel;
    edit_brigthness: TSpinEdit;
    Panel2: TPanel;
    edit_contrast: TSpinEdit;
    Panel3: TPanel;
    combo_awb: TComboBox;
    Panel4: TPanel;
    combo_exposure: TComboBox;
    Panel5: TPanel;
    edit_ISO: TSpinEdit;
    Panel6: TPanel;
    combo_metering: TComboBox;
    GroupBox2: TGroupBox;
    Panel7: TPanel;
    edit_image_size: TSpinEdit;
    Panel8: TPanel;
    edit_image_quality: TSpinEdit;
    Panel9: TPanel;
    combo_image_encoder: TComboBox;
    GroupBox3: TGroupBox;
    Panel10: TPanel;
    edit_video_size: TSpinEdit;
    Panel11: TPanel;
    edit_video_bitrate: TSpinEdit;
    Panel12: TPanel;
    Panel13: TPanel;
    edit_video_fps: TSpinEdit;
    radio_video_rectime: TRadioGroup;
    radio_networktype: TRadioGroup;
    radio_servertype: TRadioGroup;
    GroupBox4: TGroupBox;
    Panel15: TPanel;
    edit_shoot_count: TSpinEdit;
    Panel16: TPanel;
    edit_shoot_interval: TSpinEdit;
    Panel17: TPanel;
    edit_shoot_delay: TSpinEdit;
    Panel18: TPanel;
    combo_video_codec: TComboBox;
    check_stab: TCheckBox;
    Panel20: TPanel;
    combo_preview_size: TComboBox;
    btn_switch_server: TButton;
    btn_switch_network: TButton;
    btn_displayreload: TSpeedButton;
    chk_autorefresh: TCheckBox;
    GroupBox5: TGroupBox;
    Panel19: TPanel;
    edit_compas_mdec_cor_deg: TSpinEdit;
    Panel22: TPanel;
    compas_azimuth_cor: TSpinEdit;
    Panel23: TPanel;
    edit_compas_mdec_cor_min: TSpinEdit;
    GroupBox6: TGroupBox;
    label_Calib: TLabel;
    Panel24: TPanel;
    edit_shoot_speed: TSpinEdit;
    Timer1: TTimer;
    TabSheet3: TTabSheet;
    ToolBar2: TToolBar;
    btn_still: TSpeedButton;
    btn_record: TSpeedButton;
    btn_shutdown: TSpeedButton;
    btn_reboot: TSpeedButton;
    ToolButton3: TToolButton;
    ToolButton4: TToolButton;
    Panel21: TPanel;
    chk_camera_vf: TCheckBox;
    chk_camera_hf: TCheckBox;
    Panel25: TPanel;
    edit_camera_rotation: TSpinEdit;
    ToolButton8: TToolButton;
    Panel26: TPanel;
    Panel27: TPanel;
    Label1: TLabel;
    combo_ip: TComboBox;
    Panel29: TPanel;
    Label2: TLabel;
    combo_ports: TComboBox;
    panel_settings: TPanel;
    btn_readsetting: TBitBtn;
    chk_autosave: TCheckBox;
    radio_connected: TVrBlinkLed;
    GroupBox7: TGroupBox;
    Memo1: TMemo;
    btn_calibration: TButton;
    GroupBox8: TGroupBox;
    Button3: TButton;
    compas: TVrCompass;
    label_az: TLabel;
    Image1: TImage;
    btn_zerotelescope: TSpeedButton;
    label_level: TLabel;
    procedure udpDataReceived(Sender: TComponent; NumberBytes: Integer;
      FromIP: String);
    procedure combo_ipChange(Sender: TObject);
    procedure ButtonClick(Sender: TObject);
    procedure btn_displayreloadClick(Sender: TObject);
    procedure btn_rebootClick(Sender: TObject);
    procedure btn_shutdownClick(Sender: TObject);
    procedure btn_switch_serverClick(Sender: TObject);
    procedure btn_switch_networkClick(Sender: TObject);
    procedure check_cameraenabledMouseUp(Sender: TObject;
      Button: TMouseButton; Shift: TShiftState; X, Y: Integer);
    procedure FormCreate(Sender: TObject);
    procedure edit_brigthnessChange(Sender: TObject);
    procedure edit_contrastChange(Sender: TObject);
    procedure combo_awbChange(Sender: TObject);
    procedure combo_exposureChange(Sender: TObject);
    procedure combo_meteringChange(Sender: TObject);
    procedure edit_ISOChange(Sender: TObject);
    procedure edit_shoot_countChange(Sender: TObject);
    procedure edit_shoot_delayChange(Sender: TObject);
    procedure edit_shoot_intervalChange(Sender: TObject);
    procedure combo_preview_sizeChange(Sender: TObject);
    procedure edit_image_sizeChange(Sender: TObject);
    procedure edit_image_qualityChange(Sender: TObject);
    procedure combo_image_encoderChange(Sender: TObject);
    procedure edit_video_sizeChange(Sender: TObject);
    procedure edit_video_bitrateChange(Sender: TObject);
    procedure edit_video_fpsChange(Sender: TObject);
    procedure combo_video_codecChange(Sender: TObject);
    procedure check_stabMouseUp(Sender: TObject; Button: TMouseButton;
      Shift: TShiftState; X, Y: Integer);
    procedure radio_video_rectimeClick(Sender: TObject);
    procedure radio_preview_onClick(Sender: TObject);
    procedure edit_compas_mdec_cor_degChange(Sender: TObject);
    procedure edit_compas_mdec_cor_minChange(Sender: TObject);
    procedure compas_azimuth_corChange(Sender: TObject);
    procedure btn_calibrationClick(Sender: TObject);
    procedure Timer1Timer(Sender: TObject);
    procedure Button3Click(Sender: TObject);
    procedure edit_shoot_speedChange(Sender: TObject);
    procedure btn_stillClick(Sender: TObject);
    procedure btn_recordClick(Sender: TObject);
    procedure FormClose(Sender: TObject; var Action: TCloseAction);
    procedure combo_portsChange(Sender: TObject);
    procedure chk_camera_vfMouseUp(Sender: TObject; Button: TMouseButton;
      Shift: TShiftState; X, Y: Integer);
    procedure chk_camera_hfClick(Sender: TObject);
    procedure edit_camera_rotationChange(Sender: TObject);
    procedure Memo1DblClick(Sender: TObject);
    procedure SpeedButton1Click(Sender: TObject);
    procedure combo_ipClick(Sender: TObject);
    procedure radio_connectedChange(Sender: TObject);
  private
    procedure sendSetting(param: Integer; value: Integer; reloaddisplay: bool);
  public
    { Public declarations }
  end;

var
  Form1: TForm1;
  readsettings: bool;
const
MENU_BLACK                =0;
MENU_INFO                 =MENU_BLACK+1;
MENU_PARK_TELESCOPE       =MENU_INFO+1;
MENU_POWERDOWN            =MENU_PARK_TELESCOPE+1;
MENU_RESET                =MENU_POWERDOWN+1;
MENU_SAVESETTINGS         =MENU_RESET+1;
MENU_NETWORK              =MENU_SAVESETTINGS+1;
MENU_SERVER               =MENU_NETWORK+1;

MENU_CAMERA_ENABLED       =MENU_SERVER+1;
MENU_CAMERA_SHOOT_COUNT   =MENU_CAMERA_ENABLED+1;
MENU_CAMERA_SHOOT_DELAY   =MENU_CAMERA_SHOOT_COUNT+1;
MENU_CAMERA_SHOOT_INTERVAL=MENU_CAMERA_SHOOT_DELAY+1;
MENU_CAMERA_BRIGTHNESS    =MENU_CAMERA_SHOOT_INTERVAL+1;
MENU_CAMERA_CONTRAST      =MENU_CAMERA_BRIGTHNESS+1;
MENU_CAMERA_AWB           =MENU_CAMERA_CONTRAST+1;
MENU_CAMERA_EXPOSURE      =MENU_CAMERA_AWB+1;
MENU_CAMERA_ISO           =MENU_CAMERA_EXPOSURE+1;
MENU_CAMERA_STAB          =MENU_CAMERA_ISO+1;
MENU_CAMERA_METERING      =MENU_CAMERA_STAB+1;
MENU_CAMERA_SS            =MENU_CAMERA_METERING+1;
MENU_CAMERA_VF            =MENU_CAMERA_SS+1;
MENU_CAMERA_HF            =MENU_CAMERA_VF+1;
MENU_CAMERA_ROT           =MENU_CAMERA_HF+1;

MENU_CAMERA_IMAGE_SIZE    =MENU_CAMERA_ROT+1;
MENU_CAMERA_IMAGE_CODEC   =MENU_CAMERA_IMAGE_SIZE+1;
MENU_CAMERA_IMAGE_QUALITY =MENU_CAMERA_IMAGE_CODEC+1;
MENU_CAMERA_VIDEO_SIZE    =MENU_CAMERA_IMAGE_QUALITY+1;
MENU_CAMERA_VIDEO_CODEC   =MENU_CAMERA_VIDEO_SIZE+1;
MENU_CAMERA_VIDEO_QUALITY =MENU_CAMERA_VIDEO_CODEC+1;
MENU_CAMERA_VIDEO_RECTIME =MENU_CAMERA_VIDEO_QUALITY+1;
MENU_CAMERA_VIDEO_FPS     =MENU_CAMERA_VIDEO_RECTIME+1;

MENU_CAMERA_PREVIEW_SIZE  =MENU_CAMERA_VIDEO_FPS+1;
MENU_CAMERA_PREVIEW_ON	  =MENU_CAMERA_PREVIEW_SIZE+1;

MENU_COMPAS_MDEC_COR_DEG  =MENU_CAMERA_PREVIEW_ON+1;
MENU_COMPAS_MDEC_COR_MIN  =MENU_COMPAS_MDEC_COR_DEG+1;
MENU_COMPAS_AZIMUTH_COR   =MENU_COMPAS_MDEC_COR_MIN+1;
MENU_COMPAS_CALIBRATE     =MENU_COMPAS_AZIMUTH_COR+1;
MENU_COMPAS_SHOW_AZ       =MENU_COMPAS_CALIBRATE+1;

implementation

{$R *.DFM}
procedure RotateBitmap(Bmp: TBitmap; Rads: Single; AdjustSize: Boolean;
  BkColor: TColor = clNone);
var
  C: Single;
  S: Single;
  Tmp: TBitmap;
  OffsetX: Single;
  OffsetY: Single;
  Points: array[0..2] of TPoint;
begin
  C := Cos(Rads);
  S := Sin(Rads);
  Tmp := TBitmap.Create;
  try
    Tmp.TransparentColor := Bmp.TransparentColor;
    Tmp.TransparentMode := Bmp.TransparentMode;
    Tmp.Transparent := Bmp.Transparent;
    Tmp.Canvas.Brush.Color := BkColor;
    if AdjustSize then
    begin
      Tmp.Width := Round(Bmp.Width * Abs(C) + Bmp.Height * Abs(S));
      Tmp.Height := Round(Bmp.Width * Abs(S) + Bmp.Height * Abs(C));
      OffsetX := (Tmp.Width - Bmp.Width * C + Bmp.Height * S) / 2;
      OffsetY := (Tmp.Height - Bmp.Width * S - Bmp.Height * C) / 2;
    end
    else
    begin
      Tmp.Width := Bmp.Width;
      Tmp.Height := Bmp.Height;
      OffsetX := (Bmp.Width - Bmp.Width * C + Bmp.Height * S) / 2;
      OffsetY := (Bmp.Height - Bmp.Width * S - Bmp.Height * C) / 2;
    end;
    Points[0].X := Round(OffsetX);
    Points[0].Y := Round(OffsetY);
    Points[1].X := Round(OffsetX + Bmp.Width * C);
    Points[1].Y := Round(OffsetY + Bmp.Width * S);
    Points[2].X := Round(OffsetX - Bmp.Height * S);
    Points[2].Y := Round(OffsetY + Bmp.Height * C);
    PlgBlt(Tmp.Canvas.Handle, Points, Bmp.Canvas.Handle, 0, 0, Bmp.Width,
      Bmp.Height, 0, 0, 0);
    Bmp.Assign(Tmp);
  finally
    Tmp.Free;
  end;
end;

procedure TForm1.FormCreate(Sender: TObject);
begin
     readsettings:= false;
     if fileExists('ips.txt') then combo_ip.items.loadFromFile('ips.txt');
     if fileExists('ports.txt') then combo_ports.items.loadFromFile('ports.txt');
     combo_ports.ItemIndex:= 0;
end;
procedure TForm1.FormClose(Sender: TObject; var Action: TCloseAction);
begin
     combo_ip.items.SaveToFile('ips.txt');
     combo_ports.items.SaveToFile('ports.txt');
end;

procedure TForm1.udpDataReceived(Sender: TComponent; NumberBytes: Integer;
  FromIP: String);
var
   buffer: array[0..254] of char;
   param, value, valX, valY, level, step: ^integer;
begin
     New(param);
     New(value);
     New(valX);
     New(valY);
     New(level);
     New(step);
     udp.ReadBuffer(buffer, NumberBytes);
     if buffer[0] = '*' then
        begin
             radio_connected.enableblinking:= true;
             panel_settings.visible:= radio_connected.enableblinking;
        end;
     if (buffer[0] = '<') then
        begin
             Sscanf(buffer, '< %d %d', [value, level]);
             label_az.caption:=IntToStr(value^);
             compas.Heading:= value^;
             label_level.caption:= intToStr(level^);

        end;
     if (buffer[0] = '|') then
        begin
             sscanf(buffer, '| %d %d %d %d %d %d', [param, value, valX, valY, level, step]);
             memo1.lines.add('x: ' + inttostr(valX^) + '  xoff: '+IntToStr(param^) + '  y: '+ intToStr(valY^) + '  yoff: '+IntToStr(value^) + '  level: '+IntToStr(level^) + '  step: ' + inttostr(step^));
        end;
     if buffer[0] = '#' then
        begin
             readsettings:= true;
             sscanf(buffer, '# %d %d', [param,value]);
             //memo1.lines.add('reciving p:' + IntToStr(param^)+ ' v:' + inttostr(value^));
             case param^ of
                 MENU_NETWORK                         :radio_networktype.ItemIndex:= value^;
                 MENU_SERVER                          :radio_servertype.ItemIndex:= value^;
                 MENU_CAMERA_ENABLED                  :check_cameraenabled.checked:= bool(value^);
                 MENU_CAMERA_SHOOT_COUNT              :edit_shoot_count.value:= value^;
                 MENU_CAMERA_SHOOT_DELAY              :edit_shoot_delay.value:= value^;
                 MENU_CAMERA_SHOOT_INTERVAL           :edit_shoot_interval.value:= value^;
                 MENU_CAMERA_BRIGTHNESS               :edit_brigthness.value:= value^;
                 MENU_CAMERA_CONTRAST                 :edit_contrast.value:= value^;
                 MENU_CAMERA_AWB                      :combo_awb.itemindex:= value^;
                 MENU_CAMERA_EXPOSURE                 :combo_exposure.itemindex:= value^;
                 MENU_CAMERA_ISO                      :edit_iso.value:= value^;
                 MENU_CAMERA_STAB                     :check_stab.checked:= bool(value^);
                 MENU_CAMERA_METERING                 :combo_metering.itemindex:= value^;
                 MENU_CAMERA_SS                       :edit_shoot_speed.value:= value^;
                 MENU_CAMERA_VF                       :chk_camera_vf.checked:= not bool(value^);
                 MENU_CAMERA_HF                       :chk_camera_hf.checked:= not bool(value^);
                 MENU_CAMERA_ROT                      :edit_camera_rotation.value:= value^;

                 MENU_CAMERA_IMAGE_SIZE               :edit_image_size.value:= value^;
                 MENU_CAMERA_IMAGE_CODEC              :combo_image_encoder.itemindex:= value^;
                 MENU_CAMERA_IMAGE_QUALITY            :edit_image_quality.value:= value^;
                 MENU_CAMERA_VIDEO_SIZE               :edit_video_size.value:= value^;
                 MENU_CAMERA_VIDEO_CODEC              :combo_video_codec.itemindex:= value^;
                 MENU_CAMERA_VIDEO_QUALITY            :edit_video_bitrate.value:= value^;
                 MENU_CAMERA_VIDEO_RECTIME            :radio_video_rectime.ItemIndex:= value^;
                 MENU_CAMERA_VIDEO_FPS                :edit_video_fps.value:= value^;

                 MENU_CAMERA_PREVIEW_SIZE             :combo_preview_size.itemindex:= value^;
                 MENU_CAMERA_PREVIEW_ON               :radio_preview_on.ItemIndex:= value^;

                 MENU_COMPAS_MDEC_COR_DEG             :edit_compas_mdec_cor_deg.value:= value^;
                 MENU_COMPAS_MDEC_COR_MIN             :edit_compas_mdec_cor_min.value:= value^;
                 MENU_COMPAS_AZIMUTH_COR              :compas_azimuth_cor.value:= value^;
             end; //case
             readsettings:= false;
        end;
        freemem(param);
        freemem(value);
        freemem(valX);
        freemem(valY);
        freemem(level);
        freemem(step);
end;
procedure TForm1.sendSetting(param: Integer; value: Integer; reloaddisplay: bool);
var
   buffer: array[0..254] of char;
begin
     if radio_connected.enableblinking then
        begin
             SysUtils.FormatBuf(buffer, 16, '$ %d %d %d', 16, [param, value, integer(chk_autosave.checked)]);
             udp.SendBuffer(buffer, 16);
             if reloaddisplay then btn_displayreloadClick(nil);
        end;
end;

procedure TForm1.combo_ipChange(Sender: TObject);
var
   buffer: array[0..254] of char;
begin
     udp.remotehost:= combo_ip.text;
     pagecontrol1.visible:= false;
     ToolBar2.visible:= false;
     if combo_ip.text <> '' then
        begin
             buffer[0]:= '?';
             udp.SendBuffer(buffer, 255);
        end;
end;

procedure TForm1.ButtonClick(Sender: TObject);
var
   buffer: array[0..254] of char;
   buffer2: String;
   i: Integer;
begin
     if not radio_connected.enableblinking then exit;

     pagecontrol1.visible:= radio_connected.enableblinking;
     ToolBar2.visible:= radio_connected.enableblinking;

     readsettings:= true;

     udp.remotehost:= combo_ip.text;
     if radio_connected.enableblinking then
        begin
             for i:= MENU_NETWORK to MENU_COMPAS_AZIMUTH_COR do
                 begin
                      FmtStr(buffer2, '# %d', [i]);
                      //memo1.lines.add('sending ' + buffer);
                      strcopy(buffer, PChar(buffer2));
                      udp.SendBuffer(buffer, 16);
                      //sleep(100);
                 end;


        end;
     readsettings:= false;

end;

procedure TForm1.btn_displayreloadClick(Sender: TObject);
var
   buffer: array[0..10] of char;
begin
     if radio_connected.enableblinking then
        begin
             buffer[0]:= '@';
             udp.SendBuffer(buffer, 10);
             sleep(1000);
        end;
end;

procedure TForm1.btn_rebootClick(Sender: TObject);
var
   buffer: array[0..10] of char;
begin
     if application.MessageBox('Do you realy want to reboot Astronom?', 'Reboot', MB_YESNO)=ID_NO then exit;
     if radio_connected.enableblinking then
        begin
             buffer[0]:= '!';
             udp.SendBuffer(buffer, 10);
             sleep(1000);
        end;

end;

procedure TForm1.btn_shutdownClick(Sender: TObject);
var
   buffer: array[0..10] of char;
begin
     if application.MessageBox('Do you realy want to shotdown Astronom?', 'Shutdown', MB_YESNO)=ID_NO then exit;
     if radio_connected.enableblinking then
        begin
             buffer[0]:= '^';
             udp.SendBuffer(buffer, 10);
             sleep(1000);
        end;
end;

procedure TForm1.btn_switch_serverClick(Sender: TObject);
var
   buffer: array[0..10] of char;
begin
     if application.MessageBox('Do you realy want to switch server type?', 'Switch server type', MB_YESNO)=ID_NO then exit;
     if radio_connected.enableblinking then
        begin
             buffer[0]:= '&';
             udp.SendBuffer(buffer, 10);
             sleep(1000);
        end;
end;

procedure TForm1.btn_switch_networkClick(Sender: TObject);
var
   buffer: array[0..10] of char;
begin
     if application.MessageBox('Do you realy want to switch network mode?', 'Switch network mode', MB_YESNO)=ID_NO then exit;
     if radio_connected.enableblinking then
        begin
             buffer[0]:= '&';buffer[1]:= '&';
             udp.SendBuffer(buffer, 10);
             sleep(1000);
        end;

end;

procedure TForm1.check_cameraenabledMouseUp(Sender: TObject;
  Button: TMouseButton; Shift: TShiftState; X, Y: Integer);
begin
     sendSetting(MENU_CAMERA_ENABLED, Integer(check_cameraenabled.checked), chk_autorefresh.checked);
end;



procedure TForm1.edit_brigthnessChange(Sender: TObject);
begin
     if readsettings then exit;
     sendSetting(MENU_CAMERA_BRIGTHNESS, edit_brigthness.value, chk_autorefresh.checked);
end;

procedure TForm1.edit_contrastChange(Sender: TObject);
begin
     if readsettings then exit;
     sendSetting(MENU_CAMERA_CONTRAST, edit_contrast.value, chk_autorefresh.checked);
end;

procedure TForm1.combo_awbChange(Sender: TObject);
begin
     if readsettings then exit;
     sendSetting(MENU_CAMERA_AWB, combo_awb.ItemIndex, chk_autorefresh.checked);
end;

procedure TForm1.combo_exposureChange(Sender: TObject);
begin
     if readsettings then exit;
     sendSetting(MENU_CAMERA_EXPOSURE, combo_exposure.ItemIndex, chk_autorefresh.checked);
end;

procedure TForm1.combo_meteringChange(Sender: TObject);
begin
     if readsettings then exit;
     sendSetting(MENU_CAMERA_METERING, combo_metering.ItemIndex, chk_autorefresh.checked);
end;

procedure TForm1.edit_ISOChange(Sender: TObject);
begin
     if readsettings then exit;
     sendSetting(MENU_CAMERA_ISO, edit_iso.value, chk_autorefresh.checked);
end;

procedure TForm1.edit_shoot_countChange(Sender: TObject);
begin
     if readsettings then exit;
     sendSetting(MENU_CAMERA_SHOOT_COUNT, edit_shoot_count.value, false);
end;

procedure TForm1.edit_shoot_delayChange(Sender: TObject);
begin
     if readsettings then exit;
     sendSetting(MENU_CAMERA_SHOOT_DELAY, edit_shoot_delay.value, false);
end;

procedure TForm1.edit_shoot_intervalChange(Sender: TObject);
begin
     if readsettings then exit;
     sendSetting(MENU_CAMERA_SHOOT_INTERVAL, edit_shoot_interval.value, false);
end;

procedure TForm1.combo_preview_sizeChange(Sender: TObject);
begin
     if readsettings then exit;
     sendSetting(MENU_CAMERA_PREVIEW_SIZE, combo_preview_size.ItemIndex, chk_autorefresh.checked);
end;

procedure TForm1.edit_image_sizeChange(Sender: TObject);
begin
     if readsettings then exit;
     sendSetting(MENU_CAMERA_IMAGE_SIZE, edit_image_size.value, false);
end;

procedure TForm1.edit_image_qualityChange(Sender: TObject);
begin
     if readsettings then exit;
     sendSetting(MENU_CAMERA_IMAGE_QUALITY, edit_image_quality.value, false);
end;

procedure TForm1.combo_image_encoderChange(Sender: TObject);
begin
     if readsettings then exit;
     sendSetting(MENU_CAMERA_IMAGE_CODEC, combo_image_encoder.ItemIndex, false);
end;

procedure TForm1.edit_video_sizeChange(Sender: TObject);
begin
     if readsettings then exit;
     sendSetting(MENU_CAMERA_VIDEO_SIZE, edit_video_size.value, false);
end;

procedure TForm1.edit_video_bitrateChange(Sender: TObject);
begin
     if readsettings then exit;
     sendSetting(MENU_CAMERA_VIDEO_QUALITY, edit_video_bitrate.value, false);
end;

procedure TForm1.edit_video_fpsChange(Sender: TObject);
begin
     if readsettings then exit;
     sendSetting(MENU_CAMERA_VIDEO_FPS, edit_video_fps.value, false);
end;

procedure TForm1.combo_video_codecChange(Sender: TObject);
begin
     if readsettings then exit;
     sendSetting(MENU_CAMERA_VIDEO_CODEC, combo_video_codec.ItemIndex, false);
end;

procedure TForm1.check_stabMouseUp(Sender: TObject; Button: TMouseButton;
  Shift: TShiftState; X, Y: Integer);
begin
     if readsettings then exit;
     sendSetting(MENU_CAMERA_STAB, Integer(not check_stab.checked), false);
end;

procedure TForm1.radio_video_rectimeClick(Sender: TObject);
begin
     if readsettings then exit;
     sendSetting(MENU_CAMERA_VIDEO_RECTIME, radio_video_rectime.ItemIndex, false);
end;

procedure TForm1.radio_preview_onClick(Sender: TObject);
begin
     if readsettings then exit;
     sendSetting(MENU_CAMERA_PREVIEW_ON, radio_preview_on.ItemIndex, chk_autorefresh.checked);
end;

procedure TForm1.edit_compas_mdec_cor_degChange(Sender: TObject);
begin
     if readsettings then exit;
     sendSetting(MENU_COMPAS_MDEC_COR_DEG, edit_compas_mdec_cor_deg.value, false);
end;

procedure TForm1.edit_compas_mdec_cor_minChange(Sender: TObject);
begin
     if readsettings then exit;
     sendSetting(MENU_COMPAS_MDEC_COR_MIN, edit_compas_mdec_cor_min.value, false);
end;

procedure TForm1.compas_azimuth_corChange(Sender: TObject);
begin
     if readsettings then exit;
     sendSetting(MENU_COMPAS_AZIMUTH_COR, compas_azimuth_cor.value, false);
end;

procedure TForm1.btn_calibrationClick(Sender: TObject);
var
   buffer: array[0..254] of char;
begin
     if not radio_connected.enableblinking then exit;
     StrCopy(buffer, 'm Calibration');
     udp.SendBuffer(buffer, 254);
     buffer[0]:= '|';buffer[1]:= '|';
     udp.SendBuffer(buffer, 254);
end;

procedure TForm1.Timer1Timer(Sender: TObject);
var
   buffer: array[0..10] of char;
begin
     if not radio_connected.enableblinking then exit;
     buffer[0]:= '<';buffer[1]:= '>';
     udp.SendBuffer(buffer, 10);
end;

procedure TForm1.Button3Click(Sender: TObject);
begin
     label_az.caption:= '';
     compas.Heading:= 0;
     timer1.Enabled:= not timer1.enabled;
end;

procedure TForm1.edit_shoot_speedChange(Sender: TObject);
begin
     if readsettings then exit;
     sendSetting(MENU_CAMERA_SS, edit_shoot_speed.value, false);
end;

procedure TForm1.btn_stillClick(Sender: TObject);
var
   buffer: array[0..10] of char;
begin
     if not radio_connected.enableblinking then exit;
     buffer[0]:= '.';
     udp.SendBuffer(buffer, 1);
end;

procedure TForm1.btn_recordClick(Sender: TObject);
var
   buffer: array[0..10] of char;
begin
     if not radio_connected.enableblinking then exit;
     buffer[0]:= ':';
     udp.SendBuffer(buffer, 1);

end;

procedure TForm1.combo_portsChange(Sender: TObject);
begin
     udp.RemotePort:= StrToIntDef(combo_ports.text, 11110);
end;

procedure TForm1.chk_camera_vfMouseUp(Sender: TObject;
  Button: TMouseButton; Shift: TShiftState; X, Y: Integer);
begin
     if readsettings then exit;
     sendSetting(MENU_CAMERA_VF, Integer(not chk_camera_vf.checked), chk_autorefresh.checked);
end;

procedure TForm1.chk_camera_hfClick(Sender: TObject);
begin
     if readsettings then exit;
     sendSetting(MENU_CAMERA_HF, Integer(not chk_camera_hf.checked), chk_autorefresh.checked);
end;

procedure TForm1.edit_camera_rotationChange(Sender: TObject);
begin
     if readsettings then exit;
     sendSetting(MENU_CAMERA_ROT, edit_camera_rotation.value, chk_autorefresh.checked);
end;

procedure TForm1.Memo1DblClick(Sender: TObject);
begin
     memo1.lines.clear;
end;

procedure TForm1.SpeedButton1Click(Sender: TObject);
begin
     if readsettings then exit;

end;

procedure TForm1.combo_ipClick(Sender: TObject);
begin
     radio_connected.enableblinking:= false;
end;

procedure TForm1.radio_connectedChange(Sender: TObject);
begin
     if not radio_connected.enableblinking then
        radio_connected.colorindex:= 1
     else
        radio_connected.colorindex:= 4;
end;

end.
