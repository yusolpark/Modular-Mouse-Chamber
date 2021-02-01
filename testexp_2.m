
%set experiment parameters
num_trials = 30;
num_channels = 6; %number of data channels (not sure how many we need yet)

%create data and metadata struct
exp.data = nan(num_trials,num_channels);
exp.metadata = app.metadata;
           
% run experiment
for t = 1:num_trials
    %send stimulus to display at cue position
    
    %wait for poke at cue position
    
    %give a reward at cue position
    
    %send stimulus to reward position
    
    %wait for poke at reward position (until timeout)
    
    %give reward at reward position (if poked before timeout)
    
    %trial is now complete and can restart
    %in data struct, save timestamp at cue poke, timestamp at reward poke,
    %cue location, reward location, anything else? timestamp at incorrect poke(s)?
    
    %calculate progress of the experiment and update GUI
    progress_text = ['Trial ' num2str(t) ' of ' num2str(num_trials)];
    app.ProgressTextLabel.Text = progress_text;
    progress = 100*t/num_trials;
    app.ph.XData = [0 progress progress 0]; 
    drawnow %update graphics
end

%save exp struct
save(exp.metadata.savedir,'exp');


%example code to send data over serial
%setup: (only have to do this once)
arduino_main = serial("COM4",'BaudRate',9600); %define arduino_main serial object
fopen(arduino_main); %open connection to serial port

%sending data
fwrite(arduino_main,1,'uint8') %send "1" byte to arduino_main
fwrite(arduino_main,2,'uint8') %send "2" byte to arduino_main


