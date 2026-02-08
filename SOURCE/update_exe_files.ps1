
$pcynlitx_path = $HOME + "\Pcynlitx";

$pcynlitx_exe_path = $pcynlitx_path + "\Pcynlitx.exe";

$pcynlitx_kernel_path = $pcynlitx_path + "\Pcynlitx_Kernel.exe";

$current_dir = Get-Location;


$pcynlitx_build_path = "$current_dir" + "\BUILD\Pcynlitx.exe";

$pcynlitx_kernel_build_path = "$current_dir" + "\BUILD\Pcynlitx_Kernel.exe";

if((Test-Path -Path $pcynlitx_build_path)){

   if(!(Test-Path -Path $pcynlitx_exe_path)){

        Copy-Item $pcynlitx_build_path -Destination $pcynlitx_path
   }
}


if((Test-Path -Path $pcynlitx_kernel_build_path)){

   if(!(Test-Path -Path $pcynlitx_kernel_path)){

        Copy-Item $pcynlitx_kernel_build_path -Destination $pcynlitx_path
   }
}