%open connection to controller 
clear mmc
%mmc.port = 'COM7';
mmc.port = "/dev/cu.usbmodem14101";
mmc.controller = serialport(mmc.port,9600);
%fopen(mmc.controller); %open connection to serial port

%set experiment parameters
num_trials = 30;
num_channels = 6; %number of data channels (not sure how many we need yet)

%create data and metadata struct
script_path = mfilename('fullpath');
exp_dir = fileparts(script_path);
app_dir = fileparts(exp_dir);
cd(app_dir);
exp.data = nan(num_trials,num_channels);
app = run_mmc;
exp.metadata = app.metadata;
           
% run experiment
for t = 1:num_trials
    %send stimulus to display at cue position
    
    write(mmc.controller, [100, 0], 'uint8');
    pause(10);

    %wait for poke at cue position
    while mmc.controller.NumBytesAvailable ==0 || read(ser,1,'uint8')~=10
        pause(0.01);
    end
    tic
    %give a reward at cue position
    write(mmc.controller, [101, 0], 'uint8');
   
    %send stimulus to reward position
    write(mmc.controller, [100, 3], 'uint8');
    
    %wait for poke at reward position (until timeout)
    while rewardPoke==0 && pokeDelay < 10 
        pokeDelay = toc;
        if mmc.controller.NumBytesAvailable>0 
            pokeLoc = read(ser,1,'uint8');
            if pokeLoc~=10
               exp.data.choicetime = datestr('now');
               exp.data.choiceLoc = pokeLoc;
               if pokeLoc == 13
                 write(mmc.controller, [101, 3], 'uint8');
               end
               rewardPoke=1;
            end
        end
        delay(0.01);
    end
    
    %calculate progress of the experiment and update GUI
    progress_text = ['Trial ' num2str(t) ' of ' num2str(num_trials)];
    app.ProgressTextLabel.Text = progress_text;
    progress = 100*t/num_trials;
    app.ph.XData = [0 progress progress 0]; 
    drawnow %update graphics    
end 
 
    %trial is now complete and can restart
    %in data struct, save timestamp at cue poke, timestamp at reward poke,
    %cue location, reward location, anything else? timestamp at incorrect poke(s)?


%save exp struct
save(exp.metadata.savedir,'exp');


%example code to send data over serial
%setup: (only have to do this once)
%arduino_main = serialport("COM4",'BaudRate',9600); %define arduino_main serial object
arduino_main = serialport(mmc.port,'BaudRate',9600); %define arduino_main serial object

%fopen(arduino_main); %open connection to serial port

%sending data
write(arduino_main,1,'uint8') %send "1" byte to arduino_mainwrite(arduino_main,2,'uint8') %send "2" byte to arduino_main

%fclose(mmc.controller); %close connection
